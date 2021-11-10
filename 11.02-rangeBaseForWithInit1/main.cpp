// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <vector>

int main()
{
  std::vector<int> v{2, 3, 4, 5, 6};

  {  // #A The scope ties idx and the loop together
    size_t idx{0};
    for(const auto& e : v) { printf("[%zd] %d\n", idx++, e); }
  }
}