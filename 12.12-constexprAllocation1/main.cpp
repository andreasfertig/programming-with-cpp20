// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if not(defined(__GNUC__) && !defined(__clang__))

struct Car {  // #A Base class for all cars
  virtual ~Car()                      = default;
  constexpr virtual int speed() const = 0;
};

// #B Various concrete cars with individual speed
struct Mercedes : Car {
  constexpr int speed() const override { return 5; }
};
struct Toyota : Car {
  constexpr int speed() const override { return 6; }
};
struct Tesla : Car {
  constexpr int speed() const override { return 9; }
};

// #C A factory function to create a car
constexpr Car* CreateCar(int i)
{
  switch(i) {
    case 0: return new Mercedes{};
    case 1: return new Toyota{};
    case 2: return new Tesla{};
  }

  return nullptr;
}

constexpr int FastestCar()
{
  int max   = -1;
  int maxId = -1;
  for(int i = 0; i < 3; ++i) {
    const auto* car = CreateCar(i);

    if(car->speed() > max) {
      max   = car->speed();
      maxId = i;
    }

    delete car;
  }

  return maxId;
}

int main()
{
  auto* c = CreateCar(1);

  constexpr auto f = FastestCar();

  static_assert(f == 2);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif