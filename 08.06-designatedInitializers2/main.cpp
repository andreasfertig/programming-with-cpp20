// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

struct Point {
  int y;
  int x = 2;  // #A Using in-class member initialization
  int z;
};

struct NamedPoint {
  std::string name;
  Point       pt;
};

// #B Initializing with designated initializers
const Point p0{3, 0, 4};

// #C Initializing all members with designated initializers
const Point p1{.y = 3, .x = 0, .z = 4};
const Point p2{.y{3}, .x{0}, .z = 4};

// #D Initializing a subset with designated initializers
const Point p3{.y = 3, .z = 4};

// #E Different order as defined in Point will not compile
// const Point p4{.x = 0, .y = 3, .z = 4};

// #F Designated initializers appearers more than once, will not compile
// const Point p5{.y = 3, .y = 4};

// #G Nested designated initializers
const NamedPoint p6{.name = "zero", .pt{.y{0}, .z{0}}};

// #H Designated initializers for the outer aggregate
const NamedPoint p7{.name = "zero", .pt{0, 0, 0}};

int main() {}