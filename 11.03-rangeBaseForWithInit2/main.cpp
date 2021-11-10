// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <vector>

int main()
{
  std::vector<int> v{2, 3, 4, 5, 6};

  for(size_t idx{0}; const auto& e : v) {
    printf("[%zd] %d\n", idx++, e);
  }
}