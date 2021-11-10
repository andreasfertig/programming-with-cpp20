// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>
#include <cstdio>

struct Weak {
  std::weak_ordering operator<=>(const Weak&) const = default;
};

struct Strong {
  std::strong_ordering
  operator<=>(const Strong&) const = default;
};

struct Combined {
  Weak   w;
  Strong s;

  auto operator<=>(const Combined&) const = default;
};

int main()
{
  Combined c;

  static_assert(
    std::is_same_v<std::weak_ordering, decltype(c <=> c)>);
}