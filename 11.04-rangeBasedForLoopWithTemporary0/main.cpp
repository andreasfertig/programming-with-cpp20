// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <vector>

class Keeper {  // #A
  std::vector<int> data{2, 3, 4};

public:
  ~Keeper() { std::cout << "dtor\n"; }

  // #B Returns by reference
  auto& items() { return data; }
};

Keeper GetKeeper()  // #C Returns by value
{
  return {};
}

void Use()
{
  // #D Use the result of GetKeeper and return over items
  for(auto& item : GetKeeper().items()) {
    std::cout << item << '\n';
  }
}

int main()
{
  Use();
}