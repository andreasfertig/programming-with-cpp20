// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <format>
#include <iostream>
#include <string>

std::string Use()
{
  const double pi  = 3.1400;
  const double num = 2.0;

  std::string s = std::format("pi {}, num {}", pi, num);

  return s;
}

int main()
{
  auto s = Use();

  std::cout << s << '\n';
}