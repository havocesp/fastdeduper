# fastdeduper

An unsane application for huge text files deduplication (keeping their order) and with batteries included.

## Author

Take a look to my GitHub profile.
 - [havocesp](https://github.com/havocesp/fastdeduper)

## Description

 - Multi-thread capable for faster results.
 - STDIN reading or multiple files support.

## Usage

```sh
# using 8 CPU cores and just one file as input (result is output to STDOUT)
fastdeduper -t 8 -f file1.txt
# reading content from STDIN
cat file1.txt | fastdeduper -t 4 -f -
```

## How to install

### Dependencies

- **cmake:** Used for building the project.
- **libboost:** Required for some of the project's functionality.

```sh
sudo apt-get update 
sudo apt-get install -y libboost-all-dev cmake
```

### Build from source

1. Clone the repository:

   ```sh
   git clone https://github.com/havocesp/fastdedupe
   cd fastdedupe
   make -j8  # 8 is the number of CPU cores to be use by make
   make install
   ```

## Changelog

- **07-10-2023:** Initial release.
   - Added multi-threading support for faster deduplication.
   - Improved STDIN handling and support for multiple input files.

## TODO

- Show any kind of progress during deduplication.
- Implement regular expressions filtering for advanced deduplication.
