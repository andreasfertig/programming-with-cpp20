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
  std::vector<int> numbers{2, 3, 4, 5, 6};            // #A

  auto filter = std::views::filter(numbers, is_odd);  // #A

  // #B
  auto transform =
    std::views::transform([](int n) { return n * 2; });

  // #C
  auto results = transform(filter);

  for(int n : results) { std::cout << n << ' '; }

  std::cout << '\n';
}

int main()
{
  ranges();
}