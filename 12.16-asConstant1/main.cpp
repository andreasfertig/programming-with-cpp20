// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

consteval auto as_constant(auto v)
{
  return v;
}

constexpr int ExpensiveCalculation(int base)
{
  return base + 1;  // Well, ... expensive
}

int main()
{
  auto value2 = as_constant(ExpensiveCalculation(2));  // #B compile-time

  ++value2;                                            // #C Compiles
}