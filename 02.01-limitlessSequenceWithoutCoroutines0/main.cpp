// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

void UseCounterValue(int i)
{
  printf("%d\n", i);
}

int main()
{
  for(int i = 0; i < 5; ++i) { UseCounterValue(i); }

  for(int i = 0; i < 5; ++i) { UseCounterValue(i); }

  // other code

  for(int i = 5; i < 10; ++i) { UseCounterValue(i); }
}