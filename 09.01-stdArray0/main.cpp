// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstddef>

template<typename T,  // #A A type template parameter
         size_t N>    // #B A non-type template parameter
struct Array {
  T data[N];
};

Array<int,  // #C Passing int as type parameter
      5>    // #D Passing 5 as non-type parameter
  myArray{};
int main() {}
