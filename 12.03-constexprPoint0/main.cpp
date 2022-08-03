// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <iostream>
#include <string>
#include <tuple>

class Point {
public:
  constexpr Point(double x, double y) noexcept
  : mX{x}
  , mY{y}
  {}

  constexpr double GetX() const noexcept { return mX; }
  constexpr double GetY() const noexcept { return mY; }

  // #A Returns void and is constexpr
  constexpr void SetX(double x) noexcept { mX = x; }
  constexpr void SetY(double y) noexcept { mY = y; }

private:
  double mX;
  double mY;
};

constexpr Point move(Point p, double x, double y)
{
  p.SetX(p.GetX() + x);
  p.SetY(p.GetY() + y);

  return p;
}

int main()
{
  constexpr Point p = move({2, 2}, 3, 2);

  printf("x:%lf y:%lf\n", p.GetX(), p.GetY());
}