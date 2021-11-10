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
  return [=](auto... args) {
    print(origin,
          // #A Forward the arguments using decltype to retrieve the type
          std::forward<decltype(args)>(args)...);
  };
}

int main()
{
  // #A Logger for steering
  auto steeringLogger = getNamedLogger("Steering"s);
  // #B Logger for breaks
  auto breakLogger = getNamedLogger("Breaks"s);

  steeringLogger("angle"s, 90);  // #C Log a steering-related message
}