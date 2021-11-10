// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <string_view>
#include <type_traits>

template<typename... Args>
constexpr void Log(std::string_view fmt, const Args&... args)
{
  if constexpr(not std::is_constant_evaluated()) {
    printf(fmt.data(), args...);
  }
}

constexpr bool Fun()
{
  Log("%s\n", "hello");

  return true;
}

int main() {}