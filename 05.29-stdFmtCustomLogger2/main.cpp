// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) && not (defined(__GNUC__) && !defined(__clang__))
#  include <algorithm>
#  include <array>
#  include <format>
#  include <iostream>
#  include <string_view>

enum LogLevel { Info, Warning, Error };

template<>
struct std::formatter<LogLevel> : std::formatter<const char*> {
  inline static const char* level_names[] = {"Info", "Warning", "Error"};

  auto format(LogLevel c, format_context& ctx)
  {
    return std::formatter<const char*>::format(level_names[c], ctx);
  }
};

template<size_t Args>
constexpr auto makeBraces()
{
  // #A Define a string with empty braces and a space
  constexpr std::array<char, 4> c{"{} "};
  // #B Calculate the size of c without the string-terminator
  constexpr auto brace_size = c.size() - 1;
  // #C Reserve 2 characters for newline and string-terminator
  constexpr auto offset{2u};
  // #D Create a std::array with the required size for all braces and  newline
  std::array<char, Args * brace_size + offset> braces{};

  // #E Braces string length is array size minus newline and  string-terminator
  constexpr auto bracesLength = (braces.size() - offset);

  auto i{0u};
  std::for_each_n(braces.begin(), bracesLength, [&](auto& element) {
    element = c[i % brace_size];
    ++i;
  });

  braces[braces.size() - offset] = '\n';  // #F Add the newline

  return braces;
}

void vlog(LogLevel level, std::string_view fmt, std::format_args&& args)
{
  std::clog << std::format("{}: ", level) << std::vformat(fmt, args);
}

template<typename... Args>
constexpr void log(LogLevel level, Args&&... args)
{
  // #A Make the format string
  constexpr auto braces = makeBraces<sizeof...(Args)>();

  vlog(level, std::string_view{braces.data()}, std::make_format_args(args...));
}

void Use()
{
  int         x{4};
  std::string share{"Amazon"};
  double      d{3'117.02};

  log(LogLevel::Info, "Share price", share, "very high:", d);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno", errno);
}

int main()
{
  Use();
}

#else

int main()
{
#  pragma message("not supported")
}

#endif