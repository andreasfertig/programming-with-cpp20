// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

struct Point {
  int y;
  int x;  // #A No in-class member initializer
  int z;
};

// #B Initializing a subset with designated initializers
const Point p3{.y = 3, .z = 4};

int main() {}