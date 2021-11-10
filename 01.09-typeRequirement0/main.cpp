// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

template<typename T>
concept containerTypes = requires(T t)
{  // #A Testing for various types in T
  typename T::value_type;
  typename T::size_type;
  typename T::allocator_type;
  typename T::iterator;
  typename T::const_iterator;
};

struct A {};

static_assert(not containerTypes<A>);
static_assert(containerTypes<std::vector<int>>);

static_assert(not containerTypes<std::array<int, 5>>);
int main() {}
