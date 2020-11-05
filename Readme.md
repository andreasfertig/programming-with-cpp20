# Companion Source Code for "Programming with C++20 - Concepts, Coroutines, Ranges, and more" 1. Edition

[![Build Status](https://github.com/andreasfertig/programming-with-cpp20/workflows/ci/badge.svg)](https://github.com/andreasfertig/programming-with-cpp20/actions/) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE.txt)

![Book cover](.artwork/cover.png)

## Code examples

This repository contains runnable source code examples from the 1. edition of [Programming with C++20 - Concepts, Coroutines, Ranges, and more](https://andreasfertig.info/books/programming-with-cpp20/), by [Andreas Fertig](https://andreasfertig.info).

### The layout of the examples

The examples are separated into different directories based on how they appear in the book.

### Running the examples

The examples are contained in a single `.cpp` file that can be easily executed in any IDE. There is also an `CMakeLists.txt` which can generate IDE projects or used to compile the example in a terminal.
This repo contains a top-level `CMakeLists.txt` which does build all the examples.

### Building the examples

You can select the compiler by setting the `CXX` environment variable.

```
mkdir programming-with-cpp20
cd programming-with-cpp20
git clone https://github.com/andreasfertig/programming-with-cpp20
mkdir build
cd build
cmake ../
cmake --build . -j
```

After that you find all the executables in `programming-with-cpp20/build/bin`.

Some of these examples use the latest C++ standard, so you will need a modern compiler in order to compile them. The latest stable versions of GCC or [Clang](https://releases.llvm.org/) are recommended. The code is not tested, but expected to work, with MSVC as well.

## License

The source code is released under the [MIT License](/LICENSE.txt).
