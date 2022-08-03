// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <vector>

class Keeper {
  std::vector<int> data{2, 3, 4};

public:
  ~Keeper() { std::cout << "dtor\n"; }

  auto& items() { return data; }
};

Keeper GetKeeper()
{
  return {};
}

int main()
{
  for(auto&& items = GetKeeper(); auto& item : items.items()) {
    std::cout << item << '\n';
  }
}