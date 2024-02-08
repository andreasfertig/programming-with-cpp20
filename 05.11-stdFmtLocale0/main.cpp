// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <clocale>
#include <format>
#include <iostream>
#include <locale>
#include <string>

using namespace std::literals;

int main()
{
  const double pi = 3.14;
  const int    i  = 1'024;

  // #A Create a German locale
  const auto locDE = std::locale("de_DE.UTF-8"s);
  // #B Create a US locale
  const auto locUS = std::locale("en_US.UTF-8"s);

  std::cout << "double with format(loc, ...)\n";
  std::cout << std::format(locUS, "𝛑 in US: {:L}\n", pi);
  std::cout << std::format(locDE, "𝛑 in DE: {:L}\n", pi);

  std::cout << "\nint with format(loc, ...)\n";
  std::cout << std::format(locUS, "1'024 in US: {:L}\n", i);
  std::cout << std::format(locDE, "1'024 in DE: {:L}\n", i);

  // #C Simulate a different system locale
  std::locale::global(locUS);
  std::cout
    << "\nint with format(...) after setting global loc\n";
  std::cout << std::format("1'024 in US: {:L}\n", i);
}