// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename... Args>
std::enable_if_t<are_same_v<T, Args...>, T> add(T&& arg, Args&&... args)
{
  return (arg + ... + args);
}

#ifdef WILL_NOT_COMPILE
void WillNotCompile()
{
  printf("%d\n", add(2, 3, 4.0));
}
#endif

int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2));
}