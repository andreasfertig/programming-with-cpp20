// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

struct Air {
  Air(int amount)
  : _amount{amount}
  {}

  void Consume(int v) { _amount -= v; }

  int Available() const { return _amount; }

private:
  int _amount;
};

struct Human {
  Human(int breath);
};

Human human{5};  // #B Create global human object
Air   air{9};    // #A Create global air object

Human::Human(int breath)
{
  air.Consume(breath);  // #C Depends on air
}

void Show()
{
  printf("%d\n", air.Available());
}

int main()
{
  Show();
}