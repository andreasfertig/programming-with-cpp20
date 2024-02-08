// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <ranges>
#include <string>

int main()
{
  const std::string firstText{"Hello"};
  const std::string secondText{"Bello"};

  const bool equal = std::ranges::equal(firstText, secondText);
}