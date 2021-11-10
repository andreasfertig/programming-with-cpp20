// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if 0
#  ifndef STRCAT_H
#    define STRCAT_H

#    include <string>
#    include <type_traits>

namespace details {
  inline std::string ConvertToBoolString(bool b)
  {
    return b ? std::string{"true"} : std::string{"false"};
  }

}  // namespace details

template<class T>
inline decltype(auto) Normalize(const T& arg)
{
  // Handle bools first, we like their string representation.
  if constexpr(std::is_same_v<std::remove_cvref_t<T>, bool>) {
    return details::ConvertToBoolString(arg);

  } else if constexpr(std::is_integral_v<T>) {
    return std::to_string(arg);

  } else {
    return (arg);
  }
}

#  endif /* STRCAT_H */

#  include <cstdio>

int main()
{
  const bool b{true};

  const auto s = Normalize(b);

  printf("%s\n", s.c_str());
}
#else
int main() {}
#endif