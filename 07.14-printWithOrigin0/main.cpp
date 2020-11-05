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

int main()
{
  // #A Passing differently spelled origins
  print("Steering"s, "angle"s, 90);
  print("steering"s, "angle"s, 75);

  // #B Declaring a global variable for the steering origin
  static const auto originSteering{"Steering"s};

  print(originSteering, "angle"s, 90);  // #C Ok, use of the global variable
  print("steering"s, "angle"s, 75);     // #D Passing steering instead of Steering
}