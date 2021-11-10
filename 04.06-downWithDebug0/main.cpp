// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>

#define DEBUG 1

void Legacy()
{
#ifdef DEBUG
  std::cout << "Debugging is enabled\n";
#endif
}

void Better()
{
  if constexpr(DEBUG) { std::cout << "Debugging is enabled\n"; }
}

constexpr bool IsDebugEnabled()
{
  return DEBUG;
}

void CloseToGood()
{
  if constexpr(IsDebugEnabled()) {
    std::cout << "Debugging is enabled\n";
  }
}

int main()
{
  Legacy();
  Better();
  CloseToGood();
}