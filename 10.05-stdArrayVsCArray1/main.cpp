// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

int main()
{
  char       cArray[]{"Hello, C++20"};  // #A Compiler deduces the size
  std::array array{"Hello, C++20"};     // #B Compiler deduces the size and type
}