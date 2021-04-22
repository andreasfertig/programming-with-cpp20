// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cstddef>

struct fixed_string {
  char data[5]{};

  constexpr fixed_string(const char* str) { std::copy_n(str, 5, data); }
};

int main()
{
  fixed_string fs{"hello"};
}