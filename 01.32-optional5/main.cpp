// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

struct COMLike {
  ~COMLike() {}    // #A Make it not default destructible
  void Release();  // #B Release all data

  // Some data fields
};

void COMLike::Release()
{
  printf("release\n");
}

template<typename T>
concept HasRelease = requires(T t)
{
  t.Release();
};

#if not defined(__clang__)
template<typename T>
concept NotTriviallyDestructible =
  not std::is_trivially_destructible_v<T>;

template<typename T>
class optional {
public:
  optional() = default;

  // #A Only if not trivially destructible
  ~optional() requires NotTriviallyDestructible<T>;

  // #B If not trivially destructible and has Release method
  ~optional() requires NotTriviallyDestructible<T> and
    HasRelease<T>;

  ~optional() = default;

  optional(
    const optional&) requires std::is_copy_constructible_v<T>
  = default;

private:
  union storage_t {
    using aligned_storage_t =
      std::aligned_storage_t<sizeof(T), alignof(T)>;
    aligned_storage_t data;

    storage_t() = default;

    T* as() { return reinterpret_cast<T*>(&data); }
    // use placement new to create an instance of T inside this
    // union
  };
  storage_t value;

  static_assert(std::is_copy_constructible_v<storage_t>);
  static_assert(std::is_trivially_destructible_v<storage_t>);

  bool has_value{true};
};

template<typename T>
optional<T>::~optional() requires NotTriviallyDestructible<T>
{
  if(has_value) { value.as()->~T(); }
}

template<typename T>
optional<T>::~optional() requires NotTriviallyDestructible<T> &&
  HasRelease<T>
{
  if(has_value) {
    value.as()->Release();
    value.as()->~T();
  }
}

#endif

struct NotCopyable {
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
};

struct Not_TriviallyDestructible {
  ~Not_TriviallyDestructible() {}
};

static_assert(not std::is_trivially_destructible_v<
              Not_TriviallyDestructible>);

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

  optional<Not_TriviallyDestructible> no{};
  optional<COMLike>                   o{};

#else
#  pragma message("not supported")
#endif
}