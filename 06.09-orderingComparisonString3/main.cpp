// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cassert>
#include <compare>

class String {
public:
  template<size_t N>
  explicit String(const char (&src)[N])
  : mData{src}
  , mLen{N}
  {}

  const char* begin() const { return mData; }
  const char* end() const { return mData + mLen; }

  auto operator<=>(const String& other) const { return Compare(*this, other); }

  bool operator==(const String& other) const
  {
    if(mLen != other.mLen) { return false; }

    return std::is_eq(  // #A Using a named comparison function
      Compare(*this, other));
  }

private:
  const char*  mData;
  const size_t mLen;

  static std::weak_ordering Compare(const String& a, const String& b);
};

std::weak_ordering String::Compare(const String& a, const String& b)
{
  if(a.mLen == b.mLen && std::equal(a.begin(), a.end(), b.begin(), b.end())) {
    return std::weak_ordering::equivalent;
  }

  if(std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end())) {
    return std::weak_ordering::less;
  }

  return std::weak_ordering::greater;
}

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