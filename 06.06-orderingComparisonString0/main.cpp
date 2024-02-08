// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cassert>

enum class Ordering { Equal, LessThan, GreaterThan };

class String {
public:
  template<size_t N>
  explicit String(const char (&src)[N])
  : mData{src}
  , mLen{N}
  {}

  // #A Helper functions which are there for completeness.
  const char* begin() const { return mData; }
  const char* end() const { return mData + mLen; }

  // #B The equality comparisons.
  friend bool operator==(const String& a, const String& b)
  {
    if(a.mLen != b.mLen) {
      return false;  // #C Early exit for performance
    }

    return Ordering::Equal == Compare(a, b);
  }

  friend bool operator!=(const String& a, const String& b)
  {
    return !(a == b);
  }

  // #D The ordering comparisons.
  friend bool operator<(const String& a, const String& b)
  {
    return Ordering::LessThan == Compare(a, b);
  }

  friend bool operator>(const String& a, const String& b)
  {
    return (b < a);
  }

  friend bool operator<=(const String& a, const String& b)
  {
    return !(b < a);
  }

  friend bool operator>=(const String& a, const String& b)
  {
    return !(a < b);
  }

private:
  const char*  mData{};
  const size_t mLen{};

  // #E The compare function which does the actual comparison.
  static Ordering Compare(const String& a, const String& b);
};

Ordering String::Compare(const String& a, const String& b)
{
  if(a.mLen == b.mLen &&
     std::equal(a.begin(), a.end(), b.begin(), b.end())) {
    return Ordering::Equal;
  }

  if(std::lexicographical_compare(
       a.begin(), a.end(), b.begin(), b.end())) {
    return Ordering::LessThan;
  }

  return Ordering::GreaterThan;
}

#define CMP_PRINT(op, expected)                                      \
  {                                                                  \
    const bool res = (op);                                           \
    assert(res == expected);                                         \
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