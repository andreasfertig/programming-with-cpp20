// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

struct NotCopyable {
  NotCopyable()                   = default;
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable(NotCopyable&&)      = default;
};

struct Resources {
  int         fileDescriptor;
  std::string messageID;

  [[no_unique_address]] NotCopyable
    nc;  // #A Ensure not copyable, but move works
};

int main()
{
  Resources r1{3, "buffer"};

  // Resources r2{r1}; // #B Does not compile
}