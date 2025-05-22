# Binary Data Representation

## Overview

This project demonstrates several low-level programming concepts in C++ related to binary data representation, performance benchmarking, memory layout, and binary file format parsing. Specifically, it includes:

* Detection of powers of two using bitwise logic
* Runtime detection of system endianness
* Two implementations of value swapping (using a temporary variable and using XOR)
* Performance comparison of the two swap methods using a timing utility
* Manual simulation and handling of a segmentation fault
* Binary parsing of a PNG image header based on known byte structure

---

## Problem Description

This project explores:

* **How to identify if an integer is a power of two**
* **How to detect the byte order (endianness) of the current machine**
* **How different implementations of swap behave in performance**
* **How to catch and log segmentation faults at runtime**
* **How to read and interpret binary fields in structured file formats (like PNG)**

---

## Explanation of Topics

### Detecting Power of Two

A number is a power of two if it has exactly one bit set in binary. The condition:

```cpp
(x & (x - 1)) == 0
```

is true only when `x` is a power of two (and `x != 0`).

---

### What is Little Endian and Big Endian?

* **Little Endian**: The least significant byte is stored at the **lowest memory address**. For example, the number `0x1234` is stored in memory as:

  ```
  Address → [0x34] [0x12]
  ```
* **Big Endian**: The most significant byte is stored first:

  ```
  Address → [0x12] [0x34]
  ```

**Why it matters**: Endianness affects how multi-byte data (e.g., `int`, `float`) is interpreted in memory. It's important for low-level programming, networking, file I/O, and cross-platform compatibility.

---

### XOR Swap vs Temp Swap

#### `swapWithTemp(a, b)`

```cpp
int temp = a;
a = b;
b = temp;
```

#### `swapWithXOR(a, b)`

```cpp
a ^= b;
b ^= a;
a ^= b;
```

### Why `swapWithTemp` is Faster:

* Modern CPUs are highly optimized for **load/store (`mov`) instructions** used in `swapWithTemp`.
* XOR-based swap involves **dependent bitwise operations** that can't be easily parallelized by the CPU pipeline.
* `swapWithXOR` also requires an extra check (`if (a == b)`).
* Compilers may inline and optimize `swapWithTemp` very efficiently; XOR swap cannot be optimized as well due to data dependency.

---

### Debugging with Hex Values (Segmentation Fault Simulation)

The program includes a function that deliberately triggers a segmentation fault by dereferencing a bogus pointer (e.g., `0xBAADF00D`). A custom signal handler is registered for `SIGSEGV` to capture the fault and print a controlled message before exiting.

This allows simulation and controlled response to memory access violations without crashing the system blindly.

---

### PNG Header Parsing

The program parses the first bytes of a PNG file to extract the following from the IHDR chunk:

* Width and height in pixels
* Bit depth
* Color type
* Compression, filter, and interlace methods

All values are read in **big-endian** order, as defined in the PNG specification.

---

## Example Output

```
[OK] isPowerOfTwo passed all tests.

[Info] Machine is Little Endian

[OK] swapWithTemp passed all tests.

[OK] swapWithXOR passed all tests.

[Info] Swap with temp took: 42 ns
[Info] Swap with XOR  took: 0 ns
[Info] Swap with temp is slower than swap with XOR.

[Test] parsePNGHeader started...
[OK] PNG signature verified.
[OK] IHDR chunk parsed.
 - Width:        764 px
 - Height:       910 px
 - Bit Depth:    8
 - Color Type:   6
 - Compression:  0
 - Filter:       0
 - Interlace:    0
[OK] parsePNGHeader completed.

[Test] testSegfault started...
[Info] Intentionally dereferencing invalid pointer 0xBAADF00D
[OK] Caught segmentation fault (signal 11).
```

---

## Explanation of Output

* All logic functions are tested using `assert`.
* Platform endianness is reported at runtime.
* Performance comparison is done for 100M swaps.
* Segmentation fault is triggered and safely logged.
* PNG metadata is extracted using binary field parsing.

---

## How to Compile and Run

### 1. Clone the Repository

```bash
git clone https://github.com/LyudmilaKostanyan/Binary-Data-Representation.git
cd Binary-Data-Representation
```

### 2. Build the Project

Use CMake to build the project:

```bash
cmake -S . -B build
cmake --build build
```

Ensure you have CMake and a C++ compiler (e.g., g++) installed.

### 3. Run the Program

#### For Linux/macOS

```bash
./build/main
```

#### For Windows (MSYS2, MinGW, or VS)

```bash
./build/main.exe
```
