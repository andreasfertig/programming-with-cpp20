// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct B {};

struct A {
  A() = default;
  explicit A(const B&) {}
  operator B() const { return {}; };
};

template<typename T>
struct Wrapper {
  template<typename U>
  Wrapper(const U&);
};

void Fun(Wrapper<A> a);  // #A Takes Wrapper<A> now

template<typename T>
template<typename U>
Wrapper<T>::Wrapper(const U&)
{}

void Fun(Wrapper<A> a) {}

int main()
{
  Fun(A{});
  Fun(B{});  // #B Does compile!
}