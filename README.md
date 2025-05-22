# Binary Data Representation

## Overview

This project demonstrates several low-level programming concepts in C++ related to binary data representation and performance benchmarking. Specifically, it includes:

* Detection of powers of two using bitwise logic
* Runtime detection of system endianness
* Two implementations of value swapping (using a temporary variable and using XOR)
* Performance comparison of the two swap methods using a timing utility

---

## Problem Description

This project explores:

* **How to identify if an integer is a power of two**
* **How to detect the byte order (endianness) of the current machine**
* **How different implementations of swap behave in performance**
* **How bitwise operations differ from arithmetic operations in practice**

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

## Example Output

```
[OK] isPowerOfTwo passed all tests.

[Info] Machine is Little Endian

[OK] swapWithTemp passed all tests.

[OK] swapWithXOR passed all tests.

[Info] Swap with temp took: 192.83 ms
[Info] Swap with XOR  took: 305.14 ms
[Info] Swap with temp is faster than swap with XOR.
```

---

## Explanation of Output

* All logical functions are tested with `assert` to ensure correctness.
* System endianness is detected and printed.
* Timings for 100 million swaps show that using a temporary variable is consistently faster than using XOR.

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
