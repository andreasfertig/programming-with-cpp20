// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>
#  include <vector>

void Use()
{
  std::vector<char> buffer{'H', 'e', 'l', 'l', 'o', ','};
  std::format_to(std::back_inserter(buffer), " {}", "World");

  for(const auto& c : buffer) { std::cout << c; }

  std::cout << '\n';
}

int main()
{
  Use();
}

#else
int main()
{
#  pragma message("not supported")
}
#endif