# C++ Function Invocation Benchmark

This repository contains a C++ project designed to benchmark and compare the performance of different function invocation techniques. Specifically, it compares the execution time of derect vs indirect function calls.

## Project Structure

- `main.cpp`: The main source file containing the benchmark code.
- `main2.cpp`: Version optimized with claude.
- `main3.cpp`: Version optimized with chatgpt.
- `CMakeLists.txt`: The CMake configuration file to build the project.
- `README.md`: This file, containing an overview of the project and results.

## How to Build and Run

### Prerequisites

- CMake 3.10 or higher
- A C++17 compatible compiler (e.g., GCC, Clang, MSVC)

### Build

```
git clone https://github.com/summeroff/cpp-function-benchmark.git
cd cpp-function-benchmark
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Results
```
Release\SpeedTest1.exe
Sum after add(): 994142223829168640
Time taken by add(): 5.24339 seconds
Sum after g(): 994142223829168640
Time taken by g(): 4.43915 seconds

Release\SpeedTest2.exe
Average time for add(): 0.00148494 seconds
Average time for g(): 0.00154665 seconds
Ratio (g/add): 1.04156

Release\SpeedTest3.exe
Average time for add(): 0.00124208 seconds
Average time for g(): 0.00140183 seconds
Ratio (g/add): 1.12862
```