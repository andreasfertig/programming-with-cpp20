// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>
#include <type_traits>
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

#if not defined(__clang__) && not defined(_MSC_VER)
template<typename... Origins>
auto getNamedLogger(Origins... origins)
{
return [... _origins = std::forward<Origins>(origins)]<typename... Ts>
  // #A Requires-clause with disjunction of is_floating_point to limit Ts
  requires(not std::disjunction_v<std::is_floating_point<Ts>...>)(
    Ts... args)
  // #B Trailing requires with disjunction and is_pointer to limit Origins to no pointers
  requires(not std::disjunction_v<std::is_pointer<Origins>...>)
{
  print(_origins..., std::forward<Ts>(args)...);
};

}

int main()
{
  auto steeringLogger = getNamedLogger("Steering"s);
  auto breakLogger    = getNamedLogger("Breaks"s, "Left"s, "Front"s);

  steeringLogger("angle"s, 90);
}
#else
int main()
{ /*keep*/
#  pragma message("not supported")
}
#endif