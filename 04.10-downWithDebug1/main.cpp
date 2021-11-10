// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if 0
import "config";
import<iostream>;

int main()
{
  if constexpr(IsDebugEnabled()) { std::cout << "Debugging is enabled\n"; }
}
#else
int main()
{
#  pragma message("Needs modules")
}
#endif