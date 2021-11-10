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

struct Magazine {
  std::string name;
  std::string isbn;
};

struct Price {
  double amount;
};

#if(__cpp_generic_lambdas >= 201707)
template<typename KEY, typename VALUE>
using MapSortedByIsbn = std::map<KEY,
                                 VALUE,
                                 decltype([]<typename T>  // #A Lambda with a template-head
                                          (const T& a,    // #B Use T as in a regular template
                                           const T& b) { return a.isbn > b.isbn; })>;

#endif

int main()
{
#if(__cpp_generic_lambdas >= 201707)
  const Book effectiveCpp{"Effective C++", "978-3-16-148410-0"};
  const Book fpCpp{"Functional Programming in C++", "978-3-20-148410-0"};

  const Magazine ix{"iX", "978-3-16-148410-0"};
  const Magazine overload{"overload", "978-3-20-148410-0"};

  const Price normal{34.95};
  const Price reduced{24.95};

  MapSortedByIsbn<Book, Price>     book2Price{{effectiveCpp, reduced}, {fpCpp, normal}};
  MapSortedByIsbn<Magazine, Price> magazine2Price{{ix, reduced}, {overload, normal}};

  for(const auto& [k, v] : book2Price) {
    printf("%s %s %f\n", k.title.c_str(), k.isbn.c_str(), v.amount);
  }

#else
#  pragma message("not supported")
#endif
}