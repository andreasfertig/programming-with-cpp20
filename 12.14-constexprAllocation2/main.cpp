// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if not(defined(__GNUC__) && !defined(__clang__))

#  include <memory>

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

constexpr std::unique_ptr<Car> CreateCar(int i)
{
  switch(i) {
    case 0: return std::make_unique<Mercedes>();
    case 1: return std::make_unique<Toyota>();
    case 2: return std::make_unique<Tesla>();
  }

  return nullptr;
}

constexpr int FastestCar()
{
  int max   = -1;
  int maxId = -1;
  for(int i = 0; i < 3; ++i) {
    if(auto car = CreateCar(i); car->speed() > max) {
      max   = car->speed();
      maxId = i;
    }
  }

  return maxId;
}

int main()
{
  auto c = CreateCar(1);

  constexpr auto f = FastestCar();

  static_assert(f == 2);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif