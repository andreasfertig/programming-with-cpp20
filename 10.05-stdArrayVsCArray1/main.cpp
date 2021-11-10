// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

int main()
{
  const char cArray[]{"Hello, C++20"};  // #A Compiler deduces the size
  // #B Compiler deduces the size and type
  const std::array array{"Hello, C++20"};
}