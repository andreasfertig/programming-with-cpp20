// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <format>
#  include <iostream>
#  include <string>

std::string Main()
{
  double pi  = 3.1400;
  double num = 2.0;

  std::string s = std::format("pi {}, num {}", pi, num);

  return s;
}

int main()
{
  auto s = Main();

  std::cout << s << '\n';
}

#else

int main()
{
#  pragma message("not supported")
}

#endif