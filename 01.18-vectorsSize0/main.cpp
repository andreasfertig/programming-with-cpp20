// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <vector>

namespace sizeType {
  auto v = std::vector<int>{3, 4, 5};

  // #A Using the correct type
  const std::vector<int>::size_type size = v.size();

}  // namespace sizeType

namespace usingAuto {
  auto       v    = std::vector<int>{3, 4, 5};
  const auto size = v.size();  // #A Let the compiler deduce the type

}  // namespace usingAuto

int main()
{
  auto      v    = std::vector<int>{3, 4, 5};
  const int size = v.size();  // #A int is the wrong type
}