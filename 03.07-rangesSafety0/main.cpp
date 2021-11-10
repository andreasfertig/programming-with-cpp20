// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

void Use()
{
  auto it = std::begin(std::string{"Urg"});
}

int main()
{
  Use();
}