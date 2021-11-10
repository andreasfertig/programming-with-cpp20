// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct B {};

struct A {
  A() = default;
  explicit A(const B&);  // #A Marked explicit
  operator B() const;
};

void Fun(A a);

void Use()
{
  Fun(A{});
  // Fun(B{}); // #B Will not compile due to explicit ctor
}

void Fun(A a) {}

A::A(const B&) {}
A::operator B() const
{
  return {};
}

int main()
{
  Use();
}