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

#if(__cpp_generic_lambdas >= 201707) && not defined(__clang__)
template<typename VALUE>
using MapBookSortedByIsbn =
  std::map<Book,
           VALUE,
           // #A Provide the lambda in-place
           decltype([](const Book& a, const Book& b) {
             return a.isbn > b.isbn;
           })>;

#endif

int main()
{
#if(__cpp_generic_lambdas >= 201707) && not defined(__clang__)
  const Book effectiveCpp{"Effective C++", "978-3-16-148410-0"};
  const Book fpCpp{"Functional Programming in C++",
                   "978-3-20-148410-0"};

  const Price normal{34.95};
  const Price reduced{24.95};

  MapBookSortedByIsbn<Price> book2Price{{effectiveCpp, reduced},
                                        {fpCpp, normal}};

  for(const auto& [k, v] : book2Price) {
    printf("%s %s %f\n", k.title.c_str(), k.isbn.c_str(), v.amount);
  }

  {
    MapBookSortedByIsbn<int> a{};
    MapBookSortedByIsbn<int> b{};

    static_assert(std::is_same_v<decltype(a), decltype(b)>);
    a = b;
  }

#else
#  pragma message("not supported")
#endif
}