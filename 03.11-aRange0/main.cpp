// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <iterator>

#if not(defined(__GNUC__) && !defined(__clang__)) && not defined(_MSC_VER)
// not present at the moment, no idea which paper brought it and if it is
// detectable
namespace std {
  struct default_sentinel_t {};
}  // namespace std
#endif

using T = int;

struct Range {
  T begin();
  T end();
};

T Range::begin()
{
  return {};
}

T Range::end()
{
  return {};
}

namespace rnges {
  struct Range {
    T                       begin();
    std::default_sentinel_t end();
  };

  T Range::begin() { return {}; }

  std::default_sentinel_t Range::end() { return {}; }
}  // namespace rnges
int main() {}
