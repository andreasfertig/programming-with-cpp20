// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<ranges>) and not defined(__clang__)
#  include <algorithm>
#  include <ranges>
#  include <string>

int main()
{
  const std::string firstText{"Hello"};
  const std::string secondText{"Bello"};

  const bool equal = std::ranges::equal(firstText, secondText);
}
#else
int main()
{

#  pragma message("not supported")
}
#endif