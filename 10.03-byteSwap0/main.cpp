// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if HAVE_integral

#  include <bit>
#  include <concepts>
#  include <cstddef>
#  include <cstdint>
#  include <utility>

constexpr auto ReverseBytes(std::integral auto value)
{
  return [&]<size_t... I>(std::index_sequence<I...>)->decltype(value)
  {
    return (
      (((value >> I * 8) & 0xff) << ((8 * sizeof(value)) - ((1 + I) * 8))) |
      ...);
  }
  (std::make_index_sequence<sizeof(value)>{});
}

constexpr auto ByteSwap(std::integral auto value)
{
  if constexpr(std::endian::native == std::endian::big ||
               (sizeof(value) == 1)) {
    return value;
  } else {
    return ReverseBytes(value);
  }
}

static_assert(ByteSwap(uint64_t(0x123456789ABCDEF0)) == 0xF0DEBC9A78563412);
static_assert(ByteSwap(uint32_t(0x12345678)) == 0x78563412);
static_assert(ByteSwap(uint16_t(0x1234)) == 0x3412);
static_assert(ByteSwap(uint8_t(0x12)) == 0x12);

int main() {}
#else
int main()
{
#  pragma message("not supported")
}
#endif