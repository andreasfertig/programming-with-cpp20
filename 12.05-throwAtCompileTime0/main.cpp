// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

constexpr bool Fun(bool b)
{
  if(b) { throw int{42}; }

  return true;
}

static_assert(Fun(false));  // #A OK
// static_assert(Fun(true));   // #B Leads to compile error due to throw

int main() {}