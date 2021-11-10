// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <format>
#  include <iostream>
#  include <string_view>

enum LogLevel { Info, Warning, Error };

// #A Log function taking function, line, and variadic arguments
void Log(LogLevel         level,
         std::string_view functionName,
         int              line,
         std::string_view fmt,
         const auto&... args)
{
  std::clog << std::format("{}:{}:{}: ",
                           static_cast<unsigned int>(level),
                           functionName,
                           line)
            << std::vformat(fmt, std::make_format_args(args...))
            << '\n';
}

// #B Macro wrapper to call Log
#  define LOG(level, fmt, ...)                                 \
    Log(level, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)

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