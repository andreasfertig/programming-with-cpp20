// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <memory>

int main()
{
  auto array =
    std::to_array("Hello, C++20");  // #A Compiler deduces the size and type

  auto array2 = std::to_array<const char>(
    "Hello, C++20");  // #B Compiler deduces the size and specify the type

  auto arrayFromList = std::to_array({3, 4, 5});  // #C Create the array inline

  int  intArray[]{3, 4, 5};
  auto movedArray = std::to_array(std::move(intArray));  // #D Move the values
}