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
          std::forward<decltype(args)>(
            args)...  // #A Forward the arguments using\newline decltype to retrieve the type
    );
  };
}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);  // #A Logger for steering
  auto breakLogger    = getNamedLogger("Breaks"s);    // #B Logger for breaks

  steeringLogger("angle"s, 90);  // #C Log a steering-related message
}