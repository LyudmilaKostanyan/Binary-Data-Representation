#include <iostream>
#include <cassert>
#include <csignal>
#include <cstdlib>
#include "kaizen.h"

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

void testIsPowerOfTwo() {
	assert(!isPowerOfTwo(0));
	assert(isPowerOfTwo(1));
	assert(isPowerOfTwo(2));
	assert(!isPowerOfTwo(3));
	assert(isPowerOfTwo(4));
	assert(!isPowerOfTwo(6));
	assert(isPowerOfTwo(8));
	assert(!isPowerOfTwo(9));
	assert(isPowerOfTwo(1024));
	std::cout << "[OK] isPowerOfTwo passed all tests.\n\n";
}

void testIsLittleEndian() {
	bool result = isLittleEndian();
	std::cout << "[Info] Machine is " << (result ? "Little Endian" : "Big Endian") << "\n\n";
}

void testSwapWithTemp() {
	int a = 5, b = 10;
	swapWithTemp(a, b);
	assert(a == 10 && b == 5);

	a = -7; b = 42;
	swapWithTemp(a, b);
	assert(a == 42 && b == -7);

	std::cout << "[OK] swapWithTemp passed all tests.\n\n";
}

void testSwapWithXOR() {
	int a = 7, b = 13;
	swapWithXOR(a, b);
	assert(a == 13 && b == 7);

	a = 100;
	swapWithXOR(a, a);
	assert(a == 100);

	std::cout << "[OK] swapWithXOR passed all tests.\n\n";
}

void testSwapTime() {
	constexpr size_t N = 100000000;
	int a = 123, b = 456;

	auto timer = zen::timer();
	timer.start();
	for (size_t i = 0; i < N; ++i)
		swapWithTemp(a, b);
	timer.stop();
	auto tempDuration = timer.duration<zen::timer::nsec>();

	timer.start();
	for (size_t i = 0; i < N; ++i)
		swapWithXOR(a, b);
	timer.stop();
	auto xorDuration = timer.duration<zen::timer::nsec>();

	std::cout << "[Info] Swap with temp took: " << tempDuration.count() << " ns\n";
	std::cout << "[Info] Swap with XOR  took: " << xorDuration.count() << " ns\n";
	std::cout << "[Info] Swap with temp is " << (tempDuration < xorDuration ? "faster" : "slower") << " than swap with XOR.\n\n";
}

void segfaultHandler(int signum) {
	std::cout << "[OK] Caught segmentation fault (signal " << signum << ").\n\n";
	std::exit(0);
}

void testSegfault() {
	std::signal(SIGSEGV, segfaultHandler);

	std::cout << "[Test] testSegfault started...\n";
	std::cout << "[Info] Intentionally dereferencing invalid pointer 0xBAADF00D\n";

	unsigned int* ptr = reinterpret_cast<unsigned int*>(0xBAADF00D);
	int value = *ptr;
	(void)value;
}

int main() {
	testIsPowerOfTwo();
	testIsLittleEndian();
	testSwapWithTemp();
	testSwapWithXOR();
	testSwapTime();
	testSegfault();
	return 0;
}
