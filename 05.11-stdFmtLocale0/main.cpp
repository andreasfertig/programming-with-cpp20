// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <clocale>
#  include <format>
#  include <iostream>
#  include <locale>
#  include <string>

using namespace std::literals;

int main()
{
#  if not(defined(__GNUC__) && !defined(__clang__))
  double pi = 3.14;
  int    i  = 1'024;

  auto us    = "en_US.UTF-8"s;
  auto locDE = std::locale("de_DE.UTF-8");  // #A Create a German locale
  auto locUS = std::locale(us);             // #B Create a US locale

  std::cout << "double with format(loc, ...)\n";
  std::cout << std::format(locUS, "𝛑 in US: {:L}\n", pi);
  std::cout << std::format(locDE, "𝛑 in DE: {:L}\n", pi);

  std::cout << "\nint with format(loc, ...)\n";
  std::cout << std::format(locUS, "1'024 in US: {:L}\n", i);
  std::cout << std::format(locDE, "1'024 in DE: {:L}\n", i);

  // #C Simulate a different system locale
  std::locale::global(std::locale(us));
  std::cout << "\nint with format(...) after setting global loc\n";
  std::cout << std::format("1'024 in US: {:L}\n", i);

#  endif
}

#else
int main() {}
#endif