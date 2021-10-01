// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

int main()
{
  int x = 3;

  auto l1 = [y = x  // #A A lambda init-capture, creating a new variable y with x as value
  ] { return y; };

  auto l2 = [x = x  // #B The same name of x inside the lambda
  ] { return x; };  // #C Here x refers to the x of the lambda, not to the x in the outer scope
}