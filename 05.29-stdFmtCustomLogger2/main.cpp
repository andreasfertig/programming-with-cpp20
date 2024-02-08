// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <string_view>

// Part of C++23's STL
template<typename T>
constexpr std::underlying_type_t<T> to_underlying(T value)
{
  return static_cast<std::underlying_type_t<T>>(value);
}

enum LogLevel { Info, Warning, Error };

template<>
struct std::formatter<LogLevel>
: std::formatter<std::string_view> {
  inline static std::array levelNames{"Info"sv,
                                      "Warning"sv,
                                      "Error"sv};

  auto format(LogLevel c, auto& ctx) const
  {
    return std::formatter<std::string_view>::format(
      levelNames.at(to_underlying(c)), ctx);
  }
};

template<size_t Args>
constexpr auto makeBraces()
{
  // #A Define a string with empty braces and a space
  constexpr std::array<char, 4> c{"{} "};
  // #B Calculate the size of c without the  string-terminator
  constexpr auto brace_size = c.size() - 1;
  // #C Reserve 2 characters for newline and  string-terminator
  constexpr auto offset{2u};
  // #D Create a std::array with the required size for all
  // braces  and  newline
  std::array<char, Args * brace_size + offset> braces{};

  // #E Braces string length is array size minus newline and
  // string-terminator
  constexpr auto bracesLength = (braces.size() - offset);

  auto i{0u};
  std::for_each_n(
    braces.begin(), bracesLength, [&](auto& element) {
      element = c[i % brace_size];
      ++i;
    });

  braces[bracesLength] = '\n';  // #F Add the newline

  return braces;
}

void vlog(LogLevel           level,
          std::string_view   fmt,
          std::format_args&& args)
{
  std::clog << std::format("{}: ", level)
            << std::vformat(fmt, args);
}

constexpr void log(LogLevel level, const auto&... args)
{
  // #A Make the format string
  constexpr auto braces = makeBraces<sizeof...(args)>();

  vlog(level,
       std::string_view{braces.data()},
       std::make_format_args(args...));
}

int main()
{
  const std::string share{"Amazon"};
  const double      price{3'117.02};

  log(
    LogLevel::Info, "Share price", share, "very high:", price);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno:", errno);
}