// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct Car {  // #A Base class for all cars
  virtual ~Car()            = default;
  virtual int speed() const = 0;
};

// #B Various concrete cars with individual speed
struct Mercedes : Car {
  int speed() const override { return 5; }
};
struct Toyota : Car {
  int speed() const override { return 6; }
};
struct Tesla : Car {
  int speed() const override { return 9; }
};

// #C A factory function to create a car
Car* CreateCar(int i)
{
  switch(i) {
    case 0: return new Mercedes{}; break;
    case 1: return new Toyota{}; break;
    case 2: return new Tesla{}; break;
  }

  return nullptr;
}

int FastestCar()
{
  int max   = -1;
  int maxId = -1;
  for(int i = 0; i < 3; ++i) {
    auto* car = CreateCar(i);

    if(car->speed() > max) {
      max   = car->speed();
      maxId = i;
    }

    delete car;
  }

  return maxId;
}

void Use()
{
  auto* c = CreateCar(1);

  auto f = FastestCar();
}

int main()
{
  Use();
}