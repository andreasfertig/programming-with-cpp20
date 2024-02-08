// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cassert>
#include <compare>

struct Legacy {
  int a;

  // #A These define a weak order
  bool operator==(const Legacy&) const;
  bool operator<(const Legacy&) const;
};

class ShinyCpp20Class {
  Legacy mA;
  Legacy mB;

public:
  ShinyCpp20Class(int a, int b);

  std::weak_ordering  // #A
  operator<=>(const ShinyCpp20Class&) const = default;
};

// dummy values here
bool Legacy::operator==(const Legacy&) const
{
  return true;
}
bool Legacy::operator<(const Legacy&) const
{
  return true;
}

ShinyCpp20Class::ShinyCpp20Class(int a, int b)
: mA{a}
, mB{b}
{}

int main()
{
  ShinyCpp20Class sc1{2, 3};
  ShinyCpp20Class sc2{2, 3};

  assert(sc1 == sc2);
}