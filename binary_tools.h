#pragma once
#include <fstream>
#include <iostream>

namespace bin {
	bool isPowerOfTwo(unsigned int x) {
		return (x != 0 && (x & (x - 1)) == 0);
	}

	bool isLittleEndian() {
		uint16_t number = 1;
		return (*(uint8_t*)&number == 1);
	}

	void swapWithTemp(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	void swapWithXOR(int& a, int& b) {
		if (a == b)
			return;
		a ^= b;
		b ^= a;
		a ^= b;
	}

	uint32_t readBigEndian32(std::ifstream& file) {
		uint8_t bytes[4];
		file.read(reinterpret_cast<char*>(bytes), 4);
		return (uint32_t(bytes[0]) << 24) |
				(uint32_t(bytes[1]) << 16) |
				(uint32_t(bytes[2]) << 8) |
				(uint32_t(bytes[3]));
	}

	uint8_t readByte(std::ifstream& file) {
		uint8_t byte;
		file.read(reinterpret_cast<char*>(&byte), 1);
		return byte;
	}

	void parsePNGHeader(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cerr << "Error: could not open file.\n";
			return;
		}

		uint8_t signature[8];
		file.read(reinterpret_cast<char*>(signature), 8);
		const uint8_t expectedSig[8] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
		for (int i = 0; i < 8; ++i) {
			if (signature[i] != expectedSig[i]) {
				std::cerr << "Error: Not a valid PNG file.\n";
				return;
			}
		}

		std::cout << "[OK] PNG signature verified.\n";

		uint32_t ihdrLength = readBigEndian32(file);
		char chunkType[5] = {};
		file.read(chunkType, 4);

		if (std::string(chunkType) != "IHDR") {
			std::cerr << "Error: IHDR chunk not found.\n";
			return;
		}

		uint32_t width = readBigEndian32(file);
		uint32_t height = readBigEndian32(file);
		uint8_t bitDepth = readByte(file);
		uint8_t colorType = readByte(file);
		uint8_t compression = readByte(file);
		uint8_t filter = readByte(file);
		uint8_t interlace = readByte(file);

		std::cout << "[OK] IHDR chunk parsed.\n";
		std::cout << " - Width:        " << width << " px\n";
		std::cout << " - Height:       " << height << " px\n";
		std::cout << " - Bit Depth:    " << static_cast<int>(bitDepth) << "\n";
		std::cout << " - Color Type:   " << static_cast<int>(colorType) << "\n";
		std::cout << " - Compression:  " << static_cast<int>(compression) << "\n";
		std::cout << " - Filter:       " << static_cast<int>(filter) << "\n";
		std::cout << " - Interlace:    " << static_cast<int>(interlace) << "\n";
	}

	void segfaultHandler(int signum) {
		std::cout << "[OK] Caught segmentation fault (signal " << signum << ").\n\n";
		std::exit(0);
	}
}