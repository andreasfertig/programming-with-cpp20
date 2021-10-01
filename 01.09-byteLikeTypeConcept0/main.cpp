// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <concepts>
#include <type_traits>

template<typename T>
concept ByteLikeType =         // #A Define a new concept ByteLikeType
  std::is_same_v<char*, T> ||  // #B Test for char*
  std::is_same_v<unsigned char*,
                 T> ||               // #C Test for unsigned char*
  std::is_same_v<const char*, T> ||  // #D Test for const char*
  std::is_same_v<const unsigned char*,
                 T>;  // #E Test for const unsigned char*

static_assert(ByteLikeType<char*>);
static_assert(ByteLikeType<unsigned char*>);
static_assert(ByteLikeType<const char*>);

static_assert(not ByteLikeType<const char* const>);
static_assert(not ByteLikeType<char* const>);
static_assert(not ByteLikeType<int*>);
static_assert(not ByteLikeType<int>);
static_assert(not ByteLikeType<const int>);
static_assert(not ByteLikeType<double*>);

namespace conceptVersion {

  template<typename T>
  concept ByteLikeType = std::same_as<void*, T> ||
    std::same_as<char*, T> || std::same_as<unsigned char*, T> ||
    std::same_as<const void*, T> || std::same_as<const char*, T> ||
    std::same_as<const unsigned char*, T>;

  static_assert(ByteLikeType<char*>);
  static_assert(ByteLikeType<unsigned char*>);
  static_assert(ByteLikeType<const char*>);

  static_assert(not ByteLikeType<const char* const>);
  static_assert(not ByteLikeType<char* const>);
  static_assert(not ByteLikeType<int*>);
  static_assert(not ByteLikeType<int>);
  static_assert(not ByteLikeType<const int>);
  static_assert(not ByteLikeType<double*>);

}  // namespace conceptVersion

int main() {}