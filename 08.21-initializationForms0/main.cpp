// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <version>

#if(__cpp_aggregate_paren_init >= 201902L) &&                                  \
  (__cpp_designated_initializers >= 201707L) && not defined(__clang__)

int main()
{
  struct Point {
    int y;
    int x;
    int z;
  };

  struct Nested {
    int   i;
    Point pt;
  };

  struct LifeTimeExtension {
    int&& r;  // #A Notice the r-value reference
  };

  // #B Initialization of an aggregate
  Point bPt{2, 3, 5};
  Point pPt(2, 3, 5);  // #C Since C++20

  // #D Initialization of an array
  int bArray[]{2, 3, 5};
  int pArray[](2, 3, 5);  // #E Since C++20

  Nested bNested{
    9, {3, 4, 5}};  // #F Initialization of nested aggregate with nested braces
  // Nested pNested(9,( 3,4,5));// #G Nested parentheses are a different thing

  Point bDesignated{.y = 3};  // #H Designated initializers works
  // Point pDesignated(.y=3);// #I Designated initializers are not supported

  // Point bNarrowing{3.5};// #J Does not allow narrowing
  Point pNarrowing(3.5);  // #K Allows narrowing

  Point bValueInit{};     // #L Default or zero initialization
  Point pValueInit();     // #M Still a function declaration

  // #N Initialization of a built-in type
  int bBuiltIn{4};
  int pBuiltIn(4);

  LifeTimeExtension bTemporary{4};  // #O Ok
  LifeTimeExtension pTemporary(4);  // #P Dangling reference
}
#else
int main()
{
#  pragma message("not supported")
}
#endif