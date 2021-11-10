// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <memory>

int main()
{
  // #A Compiler deduces the size and type
  const auto array = std::to_array("Hello, C++20");

  // #B Compiler deduces the size and specify the type
  const auto array2 = std::to_array<const char>("Hello, C++20");

  // #C Create the array inline
  const auto arrayFromList = std::to_array({3, 4, 5});

  int intArray[]{3, 4, 5};
  // #D Move the values
  const auto movedArray = std::to_array(std::move(intArray));
}