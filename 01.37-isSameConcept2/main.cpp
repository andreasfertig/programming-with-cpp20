// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename V, typename W>
concept IsSameHelper = std::is_same_v<V, W>;

template<typename V, typename W>
concept IsSame = IsSameHelper<V, W> and IsSameHelper<W, V>;

template<typename T>
concept AlwaysTrue = true;

template<typename T, typename U>
// #A The arguments are swapped T, U vs U, T
requires IsSame<U, T>
auto add(const T& t, const U& u)
{
  return t + u;
}

template<typename T, typename U>
// #B The arguments remain unchanged
requires IsSame<T, U> and AlwaysTrue<T>
auto add(const T& t, const U& u)
{
  return t + u;
}

int main()
{
  int a = 1;
  int b = 2;

  const auto res = add(a, b);
}