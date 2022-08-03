// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

struct copyable {};

struct notCopyable {
  notCopyable(const notCopyable&)           = delete;
  notCopyable operator=(const notCopyable&) = delete;
};

template<typename T>
class optional
: public std::conditional_t<std::is_copy_constructible_v<T>,
                            copyable,
                            notCopyable> {
public:
  optional() = default;
};

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