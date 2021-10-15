// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <version>

#if defined(__cpp_lib_bit_cast)

#  include <bit>
#  include <cstdint>

int main()
{
  const float    pi  = 3.14f;
  const uint32_t pii = std::bit_cast<uint32_t>(pi);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif