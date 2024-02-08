// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

int main()
{
  const std::string s{"Hello, C++20"};

  if(s.find("Hello") != std::string::npos) { puts("Found!"); }
}