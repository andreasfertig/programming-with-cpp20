// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>
#include <cstdio>
#include <string>

#if not defined(__clang__) and not defined(_MSC_VER)
struct Address {
  std::string city;
  std::string street;
  uint32_t    street_no;

  auto operator<=>(const Address&) const = default;
};

int main()
{
  Address a1{"Heidelberg", "Hauptstrasse", 23};
  Address a2{"Heidelberg", "Hauptstrasse", 22};

  printf("%d\n", a1 > a2);
}

#else

int main()
{
#  pragma message("not supported")
}

#endif