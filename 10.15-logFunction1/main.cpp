// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) && __has_include(<source_location>)
#  include <format>
#  include <iostream>
#  include <source_location>
#  include <string_view>

enum LogLevel { Info, Warning, Error };

// #A Log function taking function, line, and variadic arguments
template<typename... Args>
void Log(LogLevel             level,
         std::source_location location,
         std::string_view     fmt,
         Args&&... args)
{
  std::clog << std::format("{}:{}:{}: ",
                           static_cast<unsigned int>(level),
                           location.function_name(),
                           location.line())
            << std::format(fmt, std::forward<Args>(args)...) << '\n';
}

// #B Macro wrapper to call Log
#  define LOG(level, fmt, ...)                                       \
    Log(level, std::source_location::current(), fmt, __VA_ARGS__)

int main()
{
  LOG(LogLevel::Info, "hello {} {} {}", 2, 3, 4);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif