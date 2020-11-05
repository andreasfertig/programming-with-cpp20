// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

int main()
{
  int c{3};

  auto twice = [=] { return c * 2; };

  return twice();
}