// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>

int main()
{
  std::array<char, 10> buffer{};
  std::format_to_n(
    buffer.data(), buffer.size() - 1, "{}, {}", "Hello", "World");

  std::cout << buffer.data() << '\n';
}

#else
int main()
{
#  pragma message("not supported")
}
#endif