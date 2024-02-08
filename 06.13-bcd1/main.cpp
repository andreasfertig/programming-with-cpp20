// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>

class BCD {
public:
  BCD(int v, int significance)
  : mSignificance{significance}
  , mValue{Adjust(v)}
  {}

  operator int() const { return mValue; }

  // #A Provide at least equality comparison
  auto operator<=>(const BCD&) const = default;

private:
  int mSignificance;  // #B The additional member just works
  int mValue;

  static int Adjust(int v);
};

int BCD::Adjust(int v)
{
  // Ok, not that sophisticated
  if(v > 9 || v < 0) { return 0; }
  return v;
}

int main()
{
  BCD a{10, 0};
  BCD b{0, 1};

  int v = a;

  return a == b;
}