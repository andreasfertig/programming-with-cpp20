// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>

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

void vlog(LogLevel           level,
          std::string_view   fmt,
          std::format_args&& args)
{
  std::clog << std::format("{}: ", level)
            << std::vformat(fmt, args) << '\n';
}

constexpr void
log(LogLevel level, std::string_view fmt, const auto&... args)
{
  vlog(level, fmt, std::make_format_args(args...));
}

int main()
{
  const std::string share{"Amazon"};
  const double      price{3'117.02};

  log(LogLevel::Info,
      "Share price {} very high: {}",
      share,
      price);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno: {}", errno);
}

#else

int main()
{
#  pragma message("not supported")
}

#endif