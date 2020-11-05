// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

template<typename T>
void PrintSorted(T c)  // #A By copy to be able to sort it
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

#ifdef WILL_NOT_COMPILE
void sortedList()
{
  std::list<int> l{36, 2, 5};

  PrintSorted(l);
}

#endif

int main()
{
  sortedVector();
}