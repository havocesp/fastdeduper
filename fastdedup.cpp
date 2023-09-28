#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <thread>
#include <cxxopts.hpp>

// Función para procesar un archivo y eliminar líneas duplicadas
void processFile(const std::string& filename, std::set<std::string>& uniqueLines) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (uniqueLines.find(line) == uniqueLines.end()) {
            uniqueLines.insert(line);
            std::cout << line << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    cxxopts::Options options(argv[0], "Eliminar líneas duplicadas de archivos o desde STDIN");
    options.add_options()
        ("t,threads", "Número máximo de hilos", cxxopts::value<int>()->default_value("1"))
        ("f,filenames", "Nombres de archivo para procesar", cxxopts::value<std::vector<std::string>>())
        ("h,help", "Mostrar ayuda");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    int numThreads = result["threads"].as<int>();
    if (numThreads <= 0) {
        std::cerr << "El número de hilos debe ser mayor que 0" << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;

    std::set<std::string> uniqueLines; // Usamos un conjunto para almacenar las líneas únicas

    // Procesar archivos dados como argumentos
    if (result.count("filenames")) {
        const std::vector<std::string>& files = result["filenames"].as<std::vector<std::string>>();
        for (const std::string& file : files) {
            if (file == "-") {
                // Leer desde STDIN si el archivo es "-"
                processFile("/dev/stdin", uniqueLines);
            } else {
                // Procesar el archivo
                threads.emplace_back(processFile, file, std::ref(uniqueLines));
            }
        }
    }

    // Limitar el número de hilos utilizados al número máximo proporcionado por el usuario
    numThreads = std::min(numThreads, static_cast<int>(threads.size()));

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    return 0;
}
