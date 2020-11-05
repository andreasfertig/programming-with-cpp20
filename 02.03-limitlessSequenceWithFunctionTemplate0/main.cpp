// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

void UseCounterValue(int i)
{
  printf("%d\n", i);
}

int counter()
{
  static int i{0};
  return i++;
}

void UseCounter()
{
  for(int i = 0; i < 5; ++i) { UseCounterValue(counter()); }

  // other code

  for(int i = 0; i < 5; ++i) { UseCounterValue(counter()); }
}

int main()
{
  UseCounter();
}