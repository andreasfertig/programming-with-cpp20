// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>
#  include <vector>

using namespace std::literals;

int main()
{
  constexpr auto fmt{"{}, {}"sv};  // #A The format string

  // #B Lookahead the resulting size in bytes
  const auto size = std::formatted_size(fmt, "Hello"sv, "World"sv);

  std::vector<char> buffer(size);  // #C Preallocate the required memory
  std::format_to(buffer.begin(), fmt, "Hello"sv, "World"sv);

  for(const auto& c : buffer) { std::cout << c; }

  std::cout << '\n';
}

#else
int main()
{
#  pragma message("not supported")
}
#endif