// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

int main()
{
  const std::string s{"Hello, C++20"};

  if(s.starts_with("Hello")) { printf("Found!\n"); }

  if(s.ends_with("C++20")) { printf("Found!\n"); }
}