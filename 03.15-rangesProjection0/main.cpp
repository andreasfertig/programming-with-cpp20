// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Use()
{
  struct Book {
    std::string title;
    std::string isbn;
  };

  std::vector<Book> books{
    {"Functional Programming in C++", "978-3-20-148410-0"},
    {"Effective C++", "978-3-16-148410-0"}};

  std::sort(
    books.begin(), books.end(), [](const auto& a, const auto& b) {
      return a.title < b.title;
    });

  for(const auto& book : books) { std::cout << book.title << '\n'; }
}

int main()
{
  Use();
}