// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <vector>

struct Point {
  int y;
  int x = 2;
  int z;
};

#include <version>

#if(__cpp_designated_initializers >= 201707L)
Point GetThePoint()  // #A Returning a Point utilizing RVO
{
  return {.y = 3, .z = 4};
}

auto GetVectorOfPoints()
{
  std::vector<Point> points{};

  points.emplace_back(
    Point{.y = 5, .z = 6});  // #A Create a Point in-place of a container

  return points;
}

int main()
{
  [[maybe_unused]] auto pt = GetThePoint();

  [[maybe_unused]] auto vectorOfPoints = GetVectorOfPoints();
}
#else
int main()
{
#  pragma message("not supported")
}
#endif