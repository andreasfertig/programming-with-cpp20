// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>
#include <utility>
#include <version>

using namespace std::literals::string_literals;

template<typename First, typename... Rest>
void print(First&& first, Rest&&... args)
{
  std::cout << "[" << first << "]";

  auto coutSpaceAndArg = [](const auto& arg) { std::cout << ' ' << arg; };

  (..., coutSpaceAndArg(args));

  std::cout << '\n';
}

template<typename... Origins>
auto getNamedLogger(Origins&&... origins)
{
  return [=]<typename... Ts>(Ts && ... args)
  {
    print(origins..., std::forward<Ts>(args)...);
  };
}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);
  auto breakLogger    = getNamedLogger("Breaks"s, "Left"s, "Front"s);

  steeringLogger("angle"s, 90);
}