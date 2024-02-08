// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <source_location>
#include <string_view>

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

int main()
{
  // #C A call to Assert with  information of Use
  Assert(1 != 2, "Not met");
}