// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct NotDefaultConstructible {
  int x;

  // #A Prevent default construction
  NotDefaultConstructible() = delete;
};

namespace privateConstructor {
  struct NotDefaultConstructible {
    int x;

  private:
    // #A Prevent default construction
    NotDefaultConstructible() = delete;
  };

  // NotDefaultConstructible ndc1; // #B This statement does not compile as
  // intended

  // #C What do you think does this statement does?
  NotDefaultConstructible ndc2{};

}  // namespace privateConstructor

int main()
{
  // NotDefaultConstructible ndc1; // #B This statement does not compile as
  // intended

  // #C What do you think does this statement does?
  NotDefaultConstructible ndc2{};
}