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

auto cmp = [](const Book& a, const Book& b)  // #A Compare lambda
{ return a.isbn > b.isbn; };

template<typename VALUE>
using MapBookSortedByIsbn =  // #B Typed map for multiple use
  std::map<Book,             // #C Use Book as type for the map
           VALUE,            // #D The value can be provided
           decltype(cmp)     // #E Type of the custom compare function
           >;

int main()
{
  const Book effectiveCpp{"Effective C++", "978-3-16-148410-0"};
  const Book fpCpp{"Functional Programming in C++",
                   "978-3-20-148410-0"};

  const Price normal{34.95};
  const Price reduced{24.95};

  // #A Use the map with Price as value
  MapBookSortedByIsbn<Price> book2Price{
    {{effectiveCpp, reduced},
     {fpCpp, normal}},  // #B Add some items to it
    cmp  // #C Sadly we have to know and pass the cmp function
  };

  for(const auto& [k, v] : book2Price) {
    printf("%s %s %f\n", k.title.c_str(), k.isbn.c_str(), v.amount);
  }
}