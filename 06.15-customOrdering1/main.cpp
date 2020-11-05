// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <compare>
#include <cstdio>
#include <string>

#if not defined(_MSC_VER) && not defined(__clang__)
struct Address {
  std::string city;
  std::string street;
  uint32_t    street_no;

  auto operator<=>(const Address& rhs) const
  {
    // #A Sort city and street using their <=>
    if(const auto& cmp = city <=> rhs.city; cmp != 0) {
      return cmp;
    } else if(const auto& scmp = street <=> rhs.street;
              scmp != 0) {
      return scmp;
    }

    // #B Next, sort street_no ascending
    return rhs.street_no <=> street_no;
  }

  // #C The default should be good enough here
  bool operator==(const Address&) const = default;
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
  return 1;
}

#endif