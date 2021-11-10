// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

int main()
{
  const char cArray[]{"Hello, C++20"};  // #A Compiler deduces the size
  // #B We need to specify the size
  const std::array<char, 13> array{"Hello, C++20"};
}