// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <iterator>

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
