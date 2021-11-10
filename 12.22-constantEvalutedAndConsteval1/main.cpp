// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

#if WILL_FAIL
constexpr int Dual(int i)
{
  if(false) {
    return CompileTime(i) + 1;
  } else {
    return 42;
  }
}

#endif

int main() {}