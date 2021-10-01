// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iostream>
#include <vector>

bool is_odd(int num)
{
  return 0 != (num % 2);
}

void stl()
{
  std::vector<int> numbers{2, 3, 4, 5, 6};  // #A

  std::vector<int> oddNumbers{};  // #B
  std::copy_if(begin(numbers),    // #C
               end(numbers),
               std::back_inserter(oddNumbers),
               is_odd);

  std::vector<int> results{};        // #D
  std::transform(begin(oddNumbers),  // #E
                 end(oddNumbers),
                 std::back_inserter(results),
                 [](int n) { return n * 2; });

  // #F
  for(int n : results) { std::cout << n << ' '; }

  std::cout << '\n';
}

int main()
{
  stl();
}