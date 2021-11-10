// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T>
constexpr T pi(3.14);

template<typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;
int main() {}
