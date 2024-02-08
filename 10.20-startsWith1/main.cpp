// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

int main()
{
  const std::string s{"Hello, C++20"};

  if(s.starts_with("Hello")) { puts("Found!"); }

  if(s.ends_with("C++20")) { puts("Found!"); }
}