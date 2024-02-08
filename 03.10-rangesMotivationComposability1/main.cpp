// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

bool is_odd(int num)
{
  return 0 != (num % 2);
}

void ranges()
{
  std::vector<int> numbers{2, 3, 4, 5, 6};  // #A

  // #B
  auto results =
    numbers | std::views::filter(is_odd) |
    std::views::transform([](int n) { return n * 2; });

  // #C
  for(int n : results) { std::cout << n << ' '; }

  std::cout << '\n';
}

int main()
{
  ranges();
}