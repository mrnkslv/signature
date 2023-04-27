#include "signature.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <functional>
#include <experimental/filesystem>
#include <cmath>
#include <algorithm>

#include "md5.h"

std::string extractDataBlock(char* src, size_t length, size_t maxDataLength) {
    std::string buffer;
    if (maxDataLength < length) {
        for (int i = 0; i < maxDataLength; i++) {
            buffer += src[i];
        }
        int paddingCount = length - maxDataLength;
        for (int i = 0; i < paddingCount; i++) {
            buffer += char(0);
        }
        return buffer;
    }
    
    for (int i = 0; i < length; i++) {
        buffer += src[i];
    }
    return buffer;
}

int getFileSignature(const char* inputFilepath, const char* outputFilepath, const int blockSize) {

    std::fstream inputFile;
    inputFile.open(inputFilepath, std::ios_base::in | std::ios_base::binary);

    std::fstream outputFile;
    outputFile.open(outputFilepath, std::ios_base::out | std::ios_base::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "can't open files" << std::endl;
        return 1;
    }

    int fileSize = std::experimental::filesystem::file_size(inputFilepath) + 1;
    char* bytes = new char[fileSize];
    inputFile.read(bytes, fileSize);

    std::cout << bytes << std::endl;

    size_t batches = ceil((double)fileSize / (double)blockSize);

    MD5 hasher;

    for (int i = 0; i < batches; i++) {
        std::string hashValue = hasher(extractDataBlock((bytes + i * blockSize), blockSize, fileSize - i * blockSize));
        outputFile << hashValue;
    }

    inputFile.close();
    outputFile.close();
    delete[] bytes;

    return 0;
}