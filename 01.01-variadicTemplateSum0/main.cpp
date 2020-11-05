// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename... Args>
auto add(Args&&... args)
{
  return (... + args);
}

int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2));
}