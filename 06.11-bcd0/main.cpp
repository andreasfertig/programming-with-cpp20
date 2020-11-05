// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cassert>

class BCD {
public:
  BCD(int v)
  : mValue{Adjust(v)}
  {}

  // #A Make it convertible to int
  operator int() const { return mValue; }

  // #B Provide at least equality comparison
  bool operator==(const BCD& rhs) const
  {
    return rhs.mValue == mValue;
  }

  bool operator!=(const BCD& rhs) const
  {
    return not(*this == rhs);
  }

private:
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
  BCD a{10};
  BCD b{0};

  int v = a;

  return a == b;
}