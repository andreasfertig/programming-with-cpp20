// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename... Ts>
inline constexpr bool are_same_v =
  std::conjunction_v<std::is_same<T, Ts>...>;

template<typename... Args>
auto add(Args&&... args)
{
  static_assert(are_same_v<Args...>);

  return (... + args);
}

int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2));
}