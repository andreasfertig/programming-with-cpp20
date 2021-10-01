// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename... Args>
requires

requires(Args... args)
{
  (... + args);                  // #A Check that args provides +
  requires are_same_v<Args...>;  // #B Check all types are the same
  requires sizeof...(Args) > 1;  // #C Check that the pack contains at least two elements
}


  auto
  add(Args&&... args)
{
  return (... + args);
}


int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2, 5));
}