// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

template<class I>
concept random_access_iterator = not requires(I t)
{
  t.sort();
};

template<random_access_iterator T>
void PrintSorted(T c)
{
  std::sort(c.begin(), c.end());

  for(const auto& e : c) { std::cout << e << ' '; }

  std::cout << '\n';
}

void sortedVector()
{
  std::vector<int> v{30, 4, 22, 5};

  PrintSorted(v);
}

template<typename T>
concept HasSortMethod = requires(T t)
{
  t.sort();
};

template<HasSortMethod T>
void PrintSorted(T c)
{
  c.sort();

  for(const auto& e : c) { std::cout << e << ' '; }

  std::cout << '\n';
}

void sortedList()
{
  std::list<int> l{36, 2, 5};

  PrintSorted(l);
}

int main()
{
  sortedVector();
  sortedList();
}