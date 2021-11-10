// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<source_location>) && not defined(__clang__)
#  include <iostream>
#  include <source_location>
#  include <string_view>

// #A Assert function taking condition, message, and source
// location
void Assert(bool                 condition,
            std::string_view     msg,
            std::source_location location =
              // #B current() is special
            std::source_location::current())
{
  if(not condition) {
    std::clog << location.function_name() << ':'
              << location.line() << ": " << msg << '\n';
  }
}

void Use()
{
  // #C A call to Assert with  information of Use
  Assert(1 != 2, "Not met");
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