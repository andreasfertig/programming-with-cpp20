// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<ranges>)
#  include <iostream>
#  include <ranges>

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
  // #G Use ranges
  std::ranges::begin(c);
}

int main()
{
  Container c{};

  Use(c);

  OtherContainer oc{};

  Use(oc);
}

#else

int main()
{
#  pragma message("not supported")
}

#endif