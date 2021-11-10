// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

struct B {};

struct A {
  A() = default;
  explicit A(const B&) {}
  operator B() const { return {}; };
};

template<typename T>
struct Wrapper {
  template<typename U>
  explicit(not std::is_convertible_v<U, T>) Wrapper(const U&);
};

void Fun(Wrapper<A> a) {}

template<typename T>
template<typename U>
Wrapper<T>::Wrapper(const U&)
{}

int main()
{
  Fun(A{});
  // Fun(B{});  // #A Does not compile anymore
}