// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <vector>

int main()
{
  std::vector<int> v{2, 3, 4, 5, 6};  // #A

  size_t idx{0};  // #B Belongs to the for but is in outer scope
  for(const auto& e : v) {
    // #C Show the position using idx
    printf("[%zd] %d\n", idx++, e);
  }
}