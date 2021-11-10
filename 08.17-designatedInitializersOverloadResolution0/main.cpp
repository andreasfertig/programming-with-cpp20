// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

struct Point {
  int y;
  int x;
  int z;
};

struct Point2D {
  int X;  // #A Note that this is a capital X
  int y;
};

// #B Two functions which overload
void Add(const Point& p, int v);
void Add(const Point2D& p, int v);

void Use()
{
  Add({.X = 3, .y = 4}, 3);  // #C Fine, selects Point2D
  Add({.y = 4, .x = 3}, 3);  // #D Fine, selects Point

  // #E Will not compile as soley .y is ambiguous
  // Add({.y = 4}, 3);
}

void Add(const Point& p, int v)
{
  printf("Point\n");
}

void Add(const Point2D& p, int v)
{
  printf("Point2D\n");
}

int main()
{
  Use();
}