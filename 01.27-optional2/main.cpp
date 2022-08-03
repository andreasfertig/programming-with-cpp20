// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T>
class optional {
public:
  optional() = default;

  optional(
    const optional&) requires std::is_copy_constructible_v<T>;
};

template<typename T>
optional<T>::optional(
  const optional<T>&) requires std::is_copy_constructible_v<T>
{}

struct NotCopyable {
  NotCopyable(const NotCopyable&)            = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
};

int main()
{
  static_assert(
    not std::is_copy_constructible_v<optional<NotCopyable>>);
  static_assert(std::is_copy_constructible_v<optional<int>>);
}