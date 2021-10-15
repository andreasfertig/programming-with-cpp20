// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

int main()
{
  char cArray[]{"Hello, C++20"};               // #A Compiler deduces the size
  std::array<char, 13> array{"Hello, C++20"};  // #B We need to specify the size
}