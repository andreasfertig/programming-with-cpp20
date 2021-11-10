// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T>
union storage_t {
  using aligned_storage_t = std::aligned_storage_t<sizeof(T), alignof(T)>;
  aligned_storage_t data;

  storage_t() = default;

  T* as() { return reinterpret_cast<T*>(&data); }
  // use placement new to create an instance of T inside this union
};

template<typename T>
class optional {
public:
  optional() = default;

  template<
    typename U,
    typename = std::enable_if_t<std::is_same_v<U, optional> and
                                std::is_copy_constructible_v<T>
                               >>
  optional(const U&);

private:
  storage_t<T> value;
};


template<typename T>
template<typename U, class>
optional<T>::optional(const U&)
{}

// #A A struct with delete copy operations
struct NotCopyable {
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
};

optional<NotCopyable> a{};
optional<NotCopyable> b = a;  // #B This should fail



int main()
{
  static_assert(std::is_copy_constructible_v<optional<NotCopyable>>);
}