// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cassert>
#include <compare>
#include <utility>

class String {
public:
  template<size_t N>
  explicit String(const char (&src)[N])
  : mData{src}
  , mLen{N}
  {}

  const char* begin() const { return mData; }
  const char* end() const { return mData + mLen; }

  auto operator<=>(const String& other) const
  {
    return std::lexicographical_compare_three_way(
      begin(), end(), other.begin(), other.end());
  }

  bool operator==(const String& other) const
  {
    return std::strong_ordering::equal == operator<=>(other);
  }

private:
  const char*  mData{};
  const size_t mLen{};
};

#define CMP_PRINT(op, expected)                                                \
  {                                                                            \
    const bool res = (op);                                                     \
    assert(res == expected);                                                   \
  }

int main()
{
  const char bufa[]{"Hello"};
  const char bufc[]{"Hello"};

  String a{bufa};
  String b{"C++20"};

  String c{bufc};
  String d{"HellO"};
  String e{"s"};

  CMP_PRINT(a == b, false);
  CMP_PRINT(a == c, true);
  CMP_PRINT(a == d, false);

  CMP_PRINT(a > b, true);
  CMP_PRINT(a < b, false);
  CMP_PRINT(a > c, false);
  CMP_PRINT(a > d, true);
  CMP_PRINT(a > e, false);
  CMP_PRINT(a < e, true);
}