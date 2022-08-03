// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <ranges>
#include <string>

int main()
{
#if WILL_NOT_COMPILE
  auto it = std::ranges::begin(std::string{"Urg"});

#endif /* WILL_NOT_COMPILE */
}