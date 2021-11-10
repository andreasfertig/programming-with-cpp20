// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

#if WILL_FAIL
consteval int CompileTime(int i)
{
  return i;
}

constexpr int Dual(int i)
{
  if(std::is_constant_evaluated()) {
    return CompileTime(i) + 1;
  } else {
    return 42;
  }
}

#endif

int main() {}