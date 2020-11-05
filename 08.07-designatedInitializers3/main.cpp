// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct Point {
  int y;
  int x = 2;
  int z;
};

#include <version>

#if(__cpp_designated_initializers >= 201707L)
void InitializationWithoutDesignatedInitializers()
{
  Point p3{};
  p3.y = 3;
  p3.z = 4;
}

const Point p3{3, 0, 4};

namespace desginatedInitializers {
  // #D Initializing a subset with designated initializers
  const Point p3{.y = 3, .z = 4};

}  // namespace desginatedInitializers
#else
#  pragma message("not supported")
#endif

int main() {}