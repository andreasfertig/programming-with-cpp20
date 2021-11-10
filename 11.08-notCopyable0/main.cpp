// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

struct Resources {
  int         fileDescriptor;
  std::string messageID;

  // #A Ensure not copyable, but move works
  Resources()                 = default;
  Resources(const Resources&) = delete;
  Resources(Resources&&)      = default;
};

int main()
{
  Resources r1{3, "buffer"};

  // Resources r2{r1}; // #B Does not compile
}