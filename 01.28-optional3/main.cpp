// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T>
union storage_t {
  using aligned_storage_t =
    std::aligned_storage_t<sizeof(T), alignof(T)>;
  aligned_storage_t data;

  storage_t() = default;

  T* as() { return reinterpret_cast<T*>(&data); }
  // use placement new to create an instance of T inside this
  // union
};

template<typename T>
class optional {
public:
  optional() = default;
  // The real constructor is omitted here because it
  // doesn't matter

  ~optional() requires(not std::is_trivially_destructible_v<T>)
  {
    if(has_value) { value.as()->~T(); }
  }

  ~optional() = default;

  optional(
    const optional&) requires std::is_copy_constructible_v<T>
  = default;

private:
  storage_t<T> value;
  bool         has_value{};
};

struct NotCopyable {
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
};

struct Not_TriviallyDestructible {
  ~Not_TriviallyDestructible() {}
};

static_assert(not std::is_trivially_destructible_v<
              Not_TriviallyDestructible>);

static_assert(std::is_copy_constructible_v<storage_t<int>>);
static_assert(std::is_trivially_destructible_v<storage_t<int>>);

int main()
{
#if not defined(__clang__)
  static_assert(
    not std::is_copy_constructible_v<optional<NotCopyable>>);
  static_assert(std::is_copy_constructible_v<optional<int>>);

  static_assert(not std::is_trivially_destructible_v<
                optional<Not_TriviallyDestructible>>);
  static_assert(
    std::is_trivially_destructible_v<optional<int>>);
#else
#  pragma message("not supported")
#endif
}