// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

#if not defined(_MSC_VER)
// #A A helper function with a default parameter
constexpr auto GetSize(const auto& t = {})
{
  return t.size();  // #B Call the size function of the container
}

// #C A concept which uses T.size
template<typename T, size_t N>
concept SizeCheck = (GetSize<T>() == N);

// #D A function that uses SizeCheck
void SendOnePing(const SizeCheck<1> auto& cont);

void SendOnePing(const SizeCheck<1> auto& cont) {}

int main()
{
  std::array<int, 1> a{};

  SendOnePing(a);
}
#else
int main()
{
#  pragma message("not supported")
}
#endif