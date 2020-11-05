// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

class SomeClass {
  int c{3};

public:
  void SomeCleverMethod()
  {
    auto twice = [=] {
      // #A Implicitly capturing this here instead of just c
      return c * 2;
    };

    // ...
    const auto v = twice();
  }
};

int main() {}