// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <format>
#include <iostream>
#include <source_location>
#include <string_view>

enum LogLevel { Info, Warning, Error };

struct Format {
  std::string_view     fmt;
  std::source_location loc;

  // #A Constructor allowing implicit conversion
  Format(
    const char*          _fmt,
    std::source_location _loc = std::source_location::current())
  : fmt{_fmt}
  , loc{_loc}
  {}
};

// #B Log now takes Format which implicitly adds source location
// information
void Log(LogLevel level, Format fmt, const auto&... args)
{
  std::clog << std::format("{}:{}:{}: ",
                           static_cast<unsigned int>(level),
                           fmt.loc.function_name(),
                           fmt.loc.line())
            << std::vformat(fmt.fmt,
                            std::make_format_args(args...))
            << '\n';
}

int main()
{
  Log(LogLevel::Info, "hello {} {} {}", 2, 3, 4);
}