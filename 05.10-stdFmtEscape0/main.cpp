// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <format>
#  include <iostream>
#  include <string>

int main()
{
  std::cout << std::format("Having the }} in a {}.", "string");

  std::cout << '\n';
}

#else
int main() {}
#endif