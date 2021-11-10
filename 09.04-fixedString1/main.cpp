// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <version>

template<typename CharT, std::size_t N>
struct fixed_string {
  CharT data[N]{};

  constexpr fixed_string(const CharT (&str)[N])
  {
    std::copy_n(str, N, data);
  }
};

#if __has_include(<ranges>) and not defined(__clang__)
template<fixed_string Str>  // #A Here we have a NTTP
struct FixedStringContainer {
  void print()
  {
    std::cout << Str.data << '\n';  // #B Use Str
  }
};

void Use()
{
  // #C We can instantiate the template with a string
  FixedStringContainer<"Hello, C++"> fc{};
  fc.print();  // #D For those who believe it only if they see
               // it
}

template<fixed_string Str>  // #A Takes the fixed string as NTTP
struct FormatString {
  // #B Store the string for easy access
  static constexpr auto fmt = Str;

  // #C Use ranges to count all the percent signs.
  static constexpr auto numArgs =
    std::ranges::count(fmt.data, '%');

  // #D For usability provide a conversion operator
  operator const auto *() const { return fmt.data; }
};

template<fixed_string Str>
constexpr auto operator"" _fs()
{
  return FormatString<Str>{};
}

void print(auto fmt, const auto&... args)
{
  printf(fmt, args...);
}

int main()
{
  fixed_string fs{"Hello, C++20"};

  print(FormatString<"%s, %s">{}, "Hello", "C++20");

  print("%s, %s"_fs, "Hello", "C++20");
}
#else
int main()
{
#  pragma message("not supported")
}
#endif