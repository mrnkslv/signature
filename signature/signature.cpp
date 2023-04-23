#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <functional>
#include <experimental/filesystem>
#include <cmath>

const int BLOCK_SIZE = 1024 * 1024; // размер блока в байтах

int main(int argc, char* argv[]) {
    
    std::string file_name = "hello.txt";
    std::fstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary);
    
    if (!file.is_open()) {

        return 1;
    }

    int file_size = std::experimental::filesystem::file_size(file_name) + 1;
    char* bytes = new char[file_size];
    file.read(bytes, file_size);
    delete[]bytes;

    std::cout << bytes << std::endl;

    size_t batches = ceil((double)file_size / (double)BLOCK_SIZE);

    for ()

    return 0;
}

