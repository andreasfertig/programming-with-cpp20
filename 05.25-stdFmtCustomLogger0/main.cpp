// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <format>
#include <iostream>
#include <string_view>

using namespace std::literals;

enum class LogLevel { Info, Warning, Error };

// Part of C++23's STL
template<typename T>
constexpr std::underlying_type_t<T> to_underlying(T value)
{
  return static_cast<std::underlying_type_t<T>>(value);
}

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

void log(LogLevel         level,
         std::string_view fmt,
         const auto&... args)
{
  std::clog << std::format("{}: "sv, level)
            << std::vformat(fmt, std::make_format_args(args...))
            << '\n';
}

int main()
{
  int         x{4};
  std::string share{"Amazon"};
  double      d{3'117.02};

  log(LogLevel::Info, "Share price {} very high: {}", share, d);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno {}", errno);
}