// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>
#include <tuple>
#include <utility>

using namespace std::literals::string_literals;

template<typename First, typename... Rest>
void print(First&& first, Rest&&... args)
{
  std::cout << "[" << first << "]";

  auto coutSpaceAndArg = [](const auto& arg) {
    std::cout << ' ' << arg;
  };

  (..., coutSpaceAndArg(args));

  std::cout << '\n';
}

template<typename... Origins>
auto getNamedLogger(Origins... origins)
{
  // #A Create an init-capture of tuple and move origins into it
  return [tup = std::make_tuple(std::forward<Origins>(
            origins)...)]<typename... Ts>(Ts... args)
  {
    std::apply(
      // #B A second lambda which is applies to the tuple values
      [&](const auto&... _origins) {
        print(_origins..., std::forward<Ts>(args)...);
      },
      tup);
  };
}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);
  auto breakLogger    = getNamedLogger("Breaks"s, "Left"s, "Front"s);

  steeringLogger("angle"s, 90);
}