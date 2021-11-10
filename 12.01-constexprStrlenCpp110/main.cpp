// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

// #A Define a constexpr function
constexpr size_t StrLen(const char* str)
{
  // #B Use a single return and recursion with the ternary operator
  return *str ? 1 + StrLen(str + 1) : 0;
}

int main()
{
  constexpr char name[]{"Scott"};
  auto           len = StrLen(name);

  printf("%zd\n", len);
}