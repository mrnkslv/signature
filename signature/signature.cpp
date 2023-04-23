#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <functional>
#include <experimental/filesystem>
#include <cmath>
#include <algorithm>

const int BLOCK_SIZE = 1024 * 1024; // размер блока в байтах

void fillBuffer(char* src, size_t length, size_t max_data_length, std::string& buffer) {
    buffer = "";
    for (int i = 0; i < max_data_length; i++) {
        buffer += src[i];
    }
    int paddingCount = length - max_data_length;
    for (int i = 0; i < paddingCount; i++) {
        buffer += char(0);
    }
}

int main(int argc, char* argv[]) {
    
    std::string input_filepath = "hello.txt";
    std::fstream input_file;
    input_file.open(input_filepath, std::ios_base::in | std::ios_base::binary);

    std::string output_filepath = "hello_out.txt";
    std::fstream output_file;
    output_file.open(output_filepath, std::ios_base::out | std::ios_base::binary);
    
    if (!input_file.is_open() && !output_file.is_open()) {

        return 1;
    }

    int file_size = std::experimental::filesystem::file_size(input_filepath) + 1;
    char* bytes = new char[file_size];
    input_file.read(bytes, file_size);

    std::cout << bytes << std::endl;

    size_t batches = ceil((double)file_size / (double)BLOCK_SIZE);

    std::string buffer;
    buffer.reserve(BLOCK_SIZE);
    std::hash<std::string> hasher;

    for (int i = 0; i < batches; i++) {
        fillBuffer((bytes + i * BLOCK_SIZE), BLOCK_SIZE, file_size, buffer);

        auto hashValue = hasher(buffer);

        output_file << hashValue;
    }

    input_file.close();
    output_file.close();
    delete[]bytes;
    
    return 0;
}

