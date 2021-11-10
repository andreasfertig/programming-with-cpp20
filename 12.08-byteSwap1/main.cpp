// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if HAVE_integral && not defined(_MSC_VER)

#  include <bit>
#  include <cassert>
#  include <concepts>
#  include <cstddef>
#  include <cstdint>
#  include <utility>

#  if defined(_MSC_VER)
#    include <Winsock2.h>
#  else
#    include <arpa/inet.h>
#  endif

constexpr auto ReverseBytes(std::integral auto value)
{
  return [&]<size_t... I>(std::index_sequence<I...>)->decltype(value)
  {
    return ((((value >> I * 8) & 0xff)
             << ((8 * sizeof(value)) - ((1 + I) * 8))) |
            ...);
  }
  (std::make_index_sequence<sizeof(value)>{});
}

template<std::integral T>
constexpr T ByteSwap(T value)
{
  if constexpr(std::endian::native == std::endian::big ||
               (sizeof(value) == 1)) {
    return value;
  } else {
    if(std::is_constant_evaluated()) {
      return ReverseBytes(value);
    } else {
      if constexpr(std::same_as<T, uint64_t>) {
        return htonl(value >> 32) |
               (static_cast<uint64_t>(htonl(value)) << 32);
      } else if constexpr(std::same_as<T, uint32_t>) {
        return htonl(value);
      } else if constexpr(std::same_as<T, uint16_t>) {
        return htons(value);
      }
    }
  }
}

static_assert(ByteSwap(uint64_t(0x123456789ABCDEF0)) ==
              0xF0DEBC9A78563412);
static_assert(ByteSwap(uint32_t(0x12345678)) == 0x78563412);
static_assert(ByteSwap(uint16_t(0x1234)) == 0x3412);
static_assert(ByteSwap(uint8_t(0x12)) == 0x12);

int main()
{
  assert(ByteSwap(uint64_t(0x123456789ABCDEF0)) ==
         0xF0DEBC9A78563412);
  assert(ByteSwap(uint32_t(0x12345678)) == 0x78563412);
  assert(ByteSwap(uint16_t(0x1234)) == 0x3412);
  assert(ByteSwap(uint8_t(0x12)) == 0x12);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif