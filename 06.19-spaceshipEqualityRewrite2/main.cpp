// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct B;

struct A {
  bool operator==(B&) const { return true; }  // #A
};

struct B {
  bool operator==(const A&) const { return false; }  // #B
};

int main()
{
  const A a{};
  B       b{};

  const bool res1 = a == b;
  const bool res2 = b == a;
}