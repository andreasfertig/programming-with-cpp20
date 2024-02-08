// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>

#ifdef WILL_NOT_COMPILE
struct Container {};     // #A Container without begin
int* begin(Container);   // #B Free-function begin for Container

struct OtherContainer {  // #C Container with begin
  int* begin();
};

void Use(auto& c)
{
  begin(c);       // #D Call ::begin(Container)
  std::begin(c);  // #E Call STL std::begin
}

int* begin(Container)  // #B Free-function begin for Container
{
  std::cout << "begin(Container)\n";
  return nullptr;
}

int* OtherContainer::begin()
{
  std::cout << "OtherContainer::begin()\n";
  return nullptr;
}

#endif

int main()
{
#ifdef WILL_NOT_COMPILE
  Container c{};

  Use(c);
#endif
}