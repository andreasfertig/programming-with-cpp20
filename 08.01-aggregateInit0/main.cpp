// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct Aggregate {
  int a = 5;  // #A Equal in-class initializer
  int b{7};   // #B Braced in-class initializer
};

int main()
{
  Aggregate ag{};

  return ag.a + ag.b;
}