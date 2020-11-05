// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <map>
#include <string>
#include <version>

struct Book {
  std::string title;
  std::string isbn;
};

struct Price {
  double amount;
};

auto cmp = [](auto& a, auto& b) { return a.isbn > b.isbn; };
template<typename VALUE>
using MapBookSortedByIsbn = std::map<Book, VALUE, decltype(cmp)>;

int main()
{
  const Book effectiveCpp{"Effective C++", "978-3-16-148410-0"};
  const Book fpCpp{"Functional Programming in C++", "978-3-20-148410-0"};

  const Price normal{34.95};
  const Price reduced{24.95};

  MapBookSortedByIsbn<Price> book2Price{
    {effectiveCpp, reduced}, {fpCpp, normal}
    // #A cmp is gone
  };

  for(const auto& [k, v] : book2Price) {
    printf("%s %s %f\n", k.title.c_str(), k.isbn.c_str(), v.amount);
  }
}