// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <chrono>
#include <format>
#include <iostream>
#include <string_view>

using namespace std::string_view_literals;
using namespace std::string_literals;

// Part of C++23's STL
template<typename T>
constexpr std::underlying_type_t<T> to_underlying(T value)
{
  return static_cast<std::underlying_type_t<T>>(value);
}

enum LogLevel { Info, Warning, Error };

template<>
struct std::formatter<LogLevel> : std::formatter<std::string_view> {
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
  constexpr std::array<char, 4> c{"{} "};
  constexpr auto                brace_size = c.size() - 1;
  constexpr auto                offset{2u};
  std::array<char, (Args + 1) * brace_size + offset> braces{};
  for(auto i{0u}; i != braces.size() - offset; ++i) {
    braces[i] = c[i % brace_size];
  }
  braces[braces.size() - offset] = '\n';

  return braces;
}

std::chrono::time_point<std::chrono::system_clock> GetTime()
{
  //  return std::time(nullptr);
  //  return 1605722947;
  return std::chrono::system_clock::now();
}

void vlog(std::string_view fmt, std::format_args&& args)
{
  const auto t = GetTime();
  std::clog << std::format("[{:%Y-%m-%d-%H:%M:%S}] "sv, t)
            << std::vformat(fmt, args);
}

constexpr void log(LogLevel level, const auto&... args)
{
  ///\lc{}{Make the format string}/
  constexpr auto braces = makeBraces<sizeof...(args)>();

  vlog(std::string_view{braces.data()},
       std::make_format_args(level, args...));
}

int main()
{
  int         x{4};
  std::string share{"Amazon"s};
  double      d{3'117.02};

  log(LogLevel::Info, "Share price"sv, share, "very high:"sv, d);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno"sv, errno);
}