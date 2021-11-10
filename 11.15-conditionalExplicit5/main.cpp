// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct B;
struct A;

struct A {
  A() = default;
  explicit A(int);
};

struct B {
  B() = default;
  B(int);
};

namespace withfalse {
  struct B {
    B() = default;
    explicit(false) B(int);
  };

  B::B(int) {}

  void FunB(B) {}
}  // namespace withfalse

A::A(int) {}
B::B(int) {}

void FunA(A) {}
void FunB(B) {}

int main()
{
  FunA(static_cast<A>(3));
  FunB(3);

  withfalse::FunB(3);
}