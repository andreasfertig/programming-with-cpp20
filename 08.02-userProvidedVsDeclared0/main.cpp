// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

struct UserProvided {
  UserProvided()
  { /* ... */
  }
};

struct UserDeclared {
  UserDeclared() = default;
};

int main() {}