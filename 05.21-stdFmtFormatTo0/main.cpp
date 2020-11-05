// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>

int main()
{
  std::vector<char> buffer{};
  std::format_to(std::back_inserter(buffer), "{}, {}", "Hello", "World");

  for(const auto& c : buffer) { std::cout << c; }

  std::cout << '\n';
}

#else
int main()
{
#  pragma message("not supported")
}
#endif