// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <version>

#if(__cpp_aggregate_paren_init >= 201902L)
#  include <memory>

struct Point {
  int y;
  int x;
  int z;
};

const auto* pt = new Point(4, 5);

int main()
{
  auto pt = std::make_unique<Point>(4, 5);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif