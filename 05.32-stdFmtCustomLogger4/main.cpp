// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <array>
#  include <chrono>
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
  constexpr std::array<char, 4>                      c{"{} "};
  constexpr auto                                     brace_size = c.size() - 1;
  constexpr auto                                     offset{2u};
  std::array<char, (Args + 1) * brace_size + offset> braces{};
  for(auto i{0u}; i != braces.size() - offset; ++i) {
    braces[i] = c[i % brace_size];
  }
  braces[braces.size() - offset] = '\n';

  return braces;
}

std::time_t GetTime()
{
  //  return std::time(nullptr);
  return 1605722947;
}

void vlog(std::string_view fmt, std::format_args&& args)
{
  std::time_t t = GetTime();
  std::clog << std::format("[{:%Y-%m-%d-%H:%M:%S}] ", *std::localtime(&t))
            << std::vformat(fmt, args);
}

template<typename... Args>
constexpr void log(LogLevel level, Args&&... args)
{
  ///\lc{}{Make the format string}/
  constexpr auto braces = makeBraces<sizeof...(Args)>();

  vlog(std::string_view{braces.data()}, std::make_format_args(level, args...));
}

int main()
{
  int         x{4};
  std::string share{"Amazon"};
  double      d{3'117.02};

  log(LogLevel::Info, "Share price", share, "very high:", d);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno", errno);
}

#else
int main()
{
#  pragma message("not supported")
}
#endif