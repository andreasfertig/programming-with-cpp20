// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if HAVE_integral
#  include <concepts>
#  include <vector>

int main()
{
  auto                     v    = std::vector<int>{3, 4, 5};
  const std::integral auto size = v.size();  // #A Limit the type's properties
}
#else
int main()
{
#  pragma message("not supported")
}
#endif