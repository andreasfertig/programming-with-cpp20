// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

constexpr int ExpensiveCalculation(int base)
{
  return base + 1;  // Well, ... expensive
}

void Use()
{
  auto           value1 = ExpensiveCalculation(2);  // #A run-time
  constexpr auto value2 = ExpensiveCalculation(2);  // #B compile-time

  //++value2;  // #C Doesn't compile, value2 is const
}

int main()
{
  Use();
}