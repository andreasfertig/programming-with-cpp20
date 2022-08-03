// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>
#include <utility>

using namespace std::literals::string_literals;

template<typename First, typename... Rest>
void print(First&& first, Rest&&... args)
{
  std::cout << "[" << first << "]";

  auto coutSpaceAndArg = [](const auto& arg) { std::cout << ' ' << arg; };

  (..., coutSpaceAndArg(args));

  std::cout << '\n';
}

auto getNamedLogger(const std::string origin)
{
  return [=]<typename... Ts>(Ts... args) {
    print(origin, std::forward<Ts>(args)...);
  };
}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);
  auto brakeLogger    = getNamedLogger("Brake"s);

  steeringLogger("angle"s, 90);
}