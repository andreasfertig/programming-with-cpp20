// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T, typename U>
concept IsSame = std::is_same_v<T, U>;

namespace variableTemplate {
  template<typename T, typename U>
  constexpr bool IsSame = std::is_same_v<T, U>;

}

int main()
{
  static_assert(not IsSame<int, double>);
  static_assert(IsSame<int, int>);

  static_assert(not variableTemplate::IsSame<int, double>);
  static_assert(variableTemplate::IsSame<int, int>);
}