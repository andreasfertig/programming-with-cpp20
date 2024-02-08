// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>
#include <cstdint>
#include <cstdio>
#include <string>

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