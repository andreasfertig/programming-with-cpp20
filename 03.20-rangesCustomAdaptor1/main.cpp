// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// #B A function returning a callable
auto addCurrency(const std::string& suffix)
{
  // #C Make sure you capture by copy!
  return std::views::transform(
    [suffix](auto i) { return std::to_string(i) + suffix; });
}

int main()
{
  const std::vector prices{3.95, 6.0, 95.4, 10.95, 12.90, 5.50};

  auto subView =
    prices |
    std::views::filter([](auto e) { return e < 10.0; })
    // #A Use the adaptor as usual
    | addCurrency(" €");

  for(const auto& e : subView) { std::cout << e << '\n'; }
}