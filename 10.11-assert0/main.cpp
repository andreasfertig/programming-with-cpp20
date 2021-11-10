// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string_view>

// #A Assert function taking function, line, condition, and
// message
void Assert(bool             condition,
            std::string_view msg,
            std::string_view function,
            int              line)
{
  if(not condition) {
    std::clog << function << ':'
              << line  // #B followed by function and line
              << ": " << msg  // #C and the message
              << '\n';
  }
}

// #D Macro wrapper to call Assert
#define ASSERT(condition, msg)                                 \
  Assert(condition,                                            \
         msg,                                                  \
         __FUNCTION__,                                         \
         __LINE__)  // #E Get function and line information from
                    // caller

void Use()
{
  ASSERT(1 != 2, "Not met");
}

int main()
{
  Use();
}