// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>

struct Container {};   // #A Container without begin
int* begin(Container)  // #B Free-function begin for Container
{
  std::cout << "begin(Container)\n";
  return nullptr;
}

struct OtherContainer {  // #C Container with begin
  int* begin()
  {
    std::cout << "OtherContainer::begin()\n";
    return nullptr;
  }
};

void Use(auto& c)
{
  using std::begin;  // #E Bring std::begin in the  namespace

  // #F Now both functions are in scope
  begin(c);
}

void Use()
{
  Container c{};

  Use(c);

  OtherContainer oc{};

  Use(oc);
}

int main()
{
  Use();
}