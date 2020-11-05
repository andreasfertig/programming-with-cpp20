// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>

class BCD {
public:
  constexpr BCD(int v, int significance)
  : mSignificance{significance}
  , mValue{Adjust(v)}
  {}

  constexpr operator int() const { return mValue; }

  constexpr auto operator<=>(const BCD&) const = default;  // #A Add constexpr

private:
  int mSignificance;  // #B The additional member just works
  int mValue;

  static constexpr int Adjust(int v);
};

constexpr int BCD::Adjust(int v)
{
  // Ok, not that sophisticated
  if(v > 9 || v < 0) { return 0; }
  return v;
}

int main()
{
  constexpr BCD a{10, 0};
  constexpr BCD b{0, 1};

  static_assert(a != b);
  static_assert(a < b);
}