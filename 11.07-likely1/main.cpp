// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

int main(int value, const char*[])
{
switch(value) {
             case 0: printf("Hello\n"); break;
  [[likely]] case 1: printf("World\n"); break;
             case 2: printf("C++\n"); break;
}

}