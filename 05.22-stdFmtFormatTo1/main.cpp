// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>
#  include <vector>

int main()
{
  const std::string fmt{"{}, {}"};  // #A The format string

  // #B Lookahead the resulting size in bytes
  const auto size = std::formatted_size(fmt, "Hello", "World");

  std::vector<char> buffer(size);  // #C Preallocate the required memory
  std::format_to(buffer.begin(), fmt, "Hello", "World");

  for(const auto& c : buffer) { std::cout << c; }

  std::cout << '\n';
}

#else
int main()
{
#  pragma message("not supported")
}
#endif