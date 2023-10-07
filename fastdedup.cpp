#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <thread>
#include <algorithm>

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
    int numThreads = 1; // Número predeterminado de hilos
    if (argc > 1) {
        numThreads = std::stoi(argv[1]); // Obtener el número de hilos desde el primer argumento
    }

    if (numThreads <= 0) {
        std::cerr << "El número de hilos debe ser mayor que 0" << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;

    std::set<std::string> uniqueLines; // Usamos un conjunto para almacenar las líneas únicas

    // Procesar archivos dados como argumentos a partir del segundo argumento
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-") {
            // Leer desde STDIN si el argumento es "-"
            processFile("/dev/stdin", uniqueLines);
        } else {
            // Procesar el archivo en un hilo separado
            threads.emplace_back(processFile, arg, std::ref(uniqueLines));
        }
    }

    // Limitar el número de hilos utilizados al número especificado por el usuario
    numThreads = std::min(numThreads, static_cast<int>(threads.size()));

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    return 0;
}
