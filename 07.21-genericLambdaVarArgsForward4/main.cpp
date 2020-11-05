// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>
#include <utility>

using namespace std::literals::string_literals;

#if not defined(_MSC_VER)
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
  return [... _origins = std::forward<Origins>(
            origins)]<typename... Ts>(Ts... args)
  {
    print(_origins..., std::forward<Ts>(args)...);
  };
}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);
  steeringLogger("angle"s, 90);

  auto brakeLogger = getNamedLogger("Brake"s, "Left"s, "Front"s);
  brakeLogger("force", 40);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif