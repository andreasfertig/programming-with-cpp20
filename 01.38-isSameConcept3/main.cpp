// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename V, typename W>
concept IsSameHelper = std::is_same_v<V, W>;

template<typename V, typename W>
concept IsSame = IsSameHelper<V, W> && IsSameHelper<W, V>;

template<typename T>
concept AlwaysTrue = true;

template<typename T, typename U>
// #A Inverting IsSame with not
  requires(not IsSame<T, U>)
auto add(const T& t, const U& u)
{
  return t + u;
}

template<typename T, typename U>
// #B Inverting IsSame with not
  requires((not IsSame<T, U>) and AlwaysTrue<T>)
auto add(const T& t, const U& u)
{
  return t + u;
}

int main()
{
  int    a = 1;
  double b = 2;

  // #C Call to add is again ambiguous
  // const auto res = add(a, b);
}