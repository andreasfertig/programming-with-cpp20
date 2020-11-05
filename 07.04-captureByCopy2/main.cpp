// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

class SomeClass {
  int c{3};

public:
  void SomeCleverMethod()
  {
    auto twice = [=, this]  // #A Explicit capture this as pointer
    { return c * 2; };

    // ...
    const auto v = twice();
  }
};

int main() {}