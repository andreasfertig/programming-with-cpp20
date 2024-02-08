// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <format>
#include <iostream>
#include <string>

int main()
{
  std::cout << std::format("Having the }} in a {}.", "string");

  std::cout << '\n';
}