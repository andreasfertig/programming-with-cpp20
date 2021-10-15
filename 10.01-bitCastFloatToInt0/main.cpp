// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <bit>
#include <cstdint>
#include <cstdio>
#include <cstring>

int main()
{
  float pi = 3.14f;

  uint32_t a = static_cast<uint32_t>(pi);  // #A Does not do what we want
  // uint32_t b = reinterpret_cast<uint32_t>(pi); // #B Does not compile
  uint32_t c = *reinterpret_cast<uint32_t*>(
    &pi);  // #C Uses type-punning, can result in UB

  union FloatOrInt {
    float    f;
    uint32_t i;
  };

  FloatOrInt u{pi};

  uint32_t d = u.i;  // #D A lot of code just for a simple cast

  uint32_t f{};
  memcpy(&f, &pi, sizeof(f));  // #E Copying the value

  printf("%#x\n", a);
  printf("%#x\n", c);
  printf("%#x\n", d);
  printf("%#x\n", f);
}