// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <map>
#include <string>

int main()
{
  const std::map<int, std::string> cppStds = {
    {11, "C++11"}, {14, "C++14"}, {17, "C++17"}, {20, "C++20"}};

  const int key = 20;

  if(cppStds.contains(key)) {
    std::cout << "Found\n";
  } else {
    std::cout << "Not found\n";
  }
}