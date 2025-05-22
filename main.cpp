#include <iostream>
#include "kaizen.h"

bool isPowerOfTwo(unsigned int x) {
	return x != 0 && (x & (x - 1)) == 0;
}

bool isLittleEndian() {
	uint16_t number = 1;
	return *(uint8_t*)&number == 1;
}

void swapWithTemp(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swapWithXOR(int& a, int& b) {
	if (&a == &b)
		return;
	a ^= b;
	b ^= a;
	a ^= b;
}

int main() {
	
	for (int x = 0; x < 50; x++)
	{
		if (isPowerOfTwo(x))
			std::cout << x << " is a power of two." << std::endl;
		// else
		// 	std::cout << x << " is not a power of two." << std::endl;
	}

	if (isLittleEndian())
		std::cout << "Little Endian\n";
	else
		std::cout << "Big Endian\n";

	constexpr size_t N = 100000000;
	int a = 123;
	int b = 456;

	auto timer = zen::timer();
	timer.start();
	for (size_t i = 0; i < N; ++i)
		swapWithTemp(a, b);
	timer.stop();
	auto tempDuration = timer.duration<zen::timer::msec>();

	timer.start();
	for (size_t i = 0; i < N; ++i)
		swapWithXOR(a, b);
	timer.stop();
	auto xorDuration = timer.duration<zen::timer::msec>();

	std::cout << "Swap with temp took: " << tempDuration.count() << " ms\n";
	std::cout << "Swap with XOR  took: " << xorDuration.count() << " ms\n";

	return 0;
}

