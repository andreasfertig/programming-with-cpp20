// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <version>

#include <algorithm>
#include <cstddef>
#include <iostream>

#if not(defined(__GNUC__) && !defined(__clang__)) && __has_include(<ranges>)

template<typename CharT, std::size_t N>
struct fixed_string {
  CharT data[N]{};

  constexpr fixed_string(const CharT (&str)[N])
  {
    std::copy_n(str, N, data);
  }
};

template<fixed_string Str>  // #A Takes the fixed string as NTTP
struct FormatString {
  static constexpr auto fmt =
    Str;  // #B Store the string for easy access

  // #C Use ranges to count all the percent signs.
  static constexpr auto numArgs = std::ranges::count(fmt.data, '%');

  // #D For usability provide a conversion operator
  operator const auto *() const { return fmt.data; }
};

template<fixed_string Str>
constexpr auto operator"" _fs()
{
  return FormatString<Str>{};
}

template<typename... Ts>
void print(auto fmt, const Ts&... ts)
{
  // #A Use the count of arguments and compare it to the size of  the
  // pack
  static_assert(fmt.numArgs == sizeof...(Ts));

  printf(fmt, ts...);
}

void Use()
{
  print(FormatString<"%s, %s">{}, "Hello", "C++20");

  print("%s, %s"_fs, "Hello", "C++20");
}

int main()
{
  fixed_string fs{"Hello, C++20"};

  Use();
}

#else
int main()
{
#  pragma message("not supported")
}
#endif