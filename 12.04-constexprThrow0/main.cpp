// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <stdexcept>

constexpr double divide(int a, int b)
{
  if(0 == b) {
    // #A If not 0 at compile-time, it is fine
    throw std::overflow_error("Divide by zero");
  }

  return a / b;
}

int main()
{
  constexpr auto goodConstexpr = divide(3, 2);  // #B constexpr path
  auto           badRunTime    = divide(3, 0);  // #C run-time path
}