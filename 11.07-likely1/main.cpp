// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

int main(int value, const char*[])
{
switch(value) {
             case 0: puts("Hello"); break;
  [[likely]] case 1: puts("World"); break;
             case 2: puts("C++"); break;
}

}