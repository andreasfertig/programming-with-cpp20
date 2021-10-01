// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <string>

int main()
{
  const std::string firstText{"Hello"};
  const std::string secondText{"Bello"};

  const bool equal = std::equal(firstText.begin() + 3, firstText.end(), secondText.begin());
}