#include <iostream>
#include <cassert>
#include <csignal>
#include <cstdlib>
#include <cstdint>
#include "kaizen.h"
#include "binary_tools.h"

void testIsPowerOfTwo() {
	assert(!bin::isPowerOfTwo(0));
	assert(bin::isPowerOfTwo(1));
	assert(bin::isPowerOfTwo(2));
	assert(!bin::isPowerOfTwo(3));
	assert(bin::isPowerOfTwo(4));
	assert(!bin::isPowerOfTwo(6));
	assert(bin::isPowerOfTwo(8));
	assert(!bin::isPowerOfTwo(9));
	assert(bin::isPowerOfTwo(1024));
	std::cout << "[OK] isPowerOfTwo passed all tests.\n\n";
}

void testIsLittleEndian() {
	bool result = bin::isLittleEndian();
	std::cout << "[Info] Machine is " << (result ? "Little Endian" : "Big Endian") << "\n\n";
}

void testSwapWithTemp() {
	int a = 5, b = 10;
	bin::swapWithTemp(a, b);
	assert(a == 10 && b == 5);

	a = -7; b = 42;
	bin::swapWithTemp(a, b);
	assert(a == 42 && b == -7);

	std::cout << "[OK] swapWithTemp passed all tests.\n\n";
}

void testSwapWithXOR() {
	int a = 7, b = 13;
	bin::swapWithXOR(a, b);
	assert(a == 13 && b == 7);

	a = 100;
	bin::swapWithXOR(a, a);
	assert(a == 100);

	std::cout << "[OK] swapWithXOR passed all tests.\n\n";
}

void testSwapTime() {
	constexpr size_t N = 100000000;
	int a = 123, b = 456;

	auto timer = zen::timer();
	timer.start();
	for (size_t i = 0; i < N; ++i)
		bin::swapWithTemp(a, b);
	timer.stop();
	auto tempDuration = timer.duration<zen::timer::nsec>();

	timer.start();
	for (size_t i = 0; i < N; ++i)
		bin::swapWithXOR(a, b);
	timer.stop();
	auto xorDuration = timer.duration<zen::timer::nsec>();

	std::cout << "[Info] Swap with temp took: " << tempDuration.count() << " ns\n";
	std::cout << "[Info] Swap with XOR  took: " << xorDuration.count() << " ns\n";
	std::cout << "[Info] Swap with temp is " << (tempDuration < xorDuration ? "faster" : "slower") << " than swap with XOR.\n\n";
}

void testSegfault() {
	std::signal(SIGSEGV, bin::segfaultHandler);

	std::cout << "[Test] testSegfault started...\n";
	std::cout << "[Info] Intentionally dereferencing invalid pointer 0xBAADF00D\n";

	unsigned int* ptr = reinterpret_cast<unsigned int*>(0xBAADF00D);
	int value = *ptr;
	(void)value;
}

void testParsePNGHeader() {
	std::cout << "[Test] parsePNGHeader started...\n";
	bin::parsePNGHeader("./example.png");
	std::cout << "[OK] parsePNGHeader completed.\n\n";
}

int main() {
	testIsPowerOfTwo();
	testIsLittleEndian();
	testSwapWithTemp();
	testSwapWithXOR();
	testSwapTime();
	testParsePNGHeader();
	testSegfault();
	return 0;
}
