#include "pch.h"

#include <signature.h>

#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

TEST(Main, FileOpenError) {
	int result = getFileSignature("input123.txt", "output123.txt", 10);
	EXPECT_EQ(result, 1);
}

TEST(Main, Success3Batches) {
	std::string expected = "02afb732cc2b8e8f1c1b40980b0afb98987b19bd1683da25039b2302818dd029c13247b54ef12633de9346ed10c8a3f2130d1894de2884092be367108abbe1e6";

	int result = getFileSignature("input.txt", "output.txt", 100);
	EXPECT_EQ(result, 0);

	std::fstream input_file;
	input_file.open("output.txt", std::ios_base::in | std::ios_base::binary);
	int file_size = std::experimental::filesystem::file_size("output.txt") + 1;
	char* bytes = new char[file_size];
	input_file.read(bytes, file_size);

	EXPECT_EQ(file_size - 1, expected.length());

	for (int i = 0; i < file_size - 1; i++) {
		EXPECT_EQ(expected.at(i), bytes[i]);
	}

	delete[] bytes;
}

TEST(Main, Success1Batch) {
	std::string expected = "4bdb82c01180b2ab2453a76ed7d796cf";

	int result = getFileSignature("input_single.txt", "output_single.txt", 100);
	EXPECT_EQ(result, 0);

	std::fstream input_file;
	input_file.open("output_single.txt", std::ios_base::in | std::ios_base::binary);
	int file_size = std::experimental::filesystem::file_size("output_single.txt") + 1;
	char* bytes = new char[file_size];
	input_file.read(bytes, file_size);

	EXPECT_EQ(file_size - 1, expected.length());

	for (int i = 0; i < file_size - 1; i++) {
		EXPECT_EQ(expected.at(i), bytes[i]);
	}

	delete[] bytes;
}