// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename U>
concept same_as = std::is_same_v<std::remove_cvref_t<T>,
                                 std::remove_cvref_t<U>>;

template<typename T, typename... Ts>
constexpr bool are_same_v =
  std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
struct first_arg {
  using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template<typename... Args>
concept Addable = requires(Args... args) {
  (... + args);
  requires are_same_v<Args...>;
  requires sizeof...(Args) > 1;
  {
    (... + args)
  } noexcept -> same_as<first_arg_t<Args...>>;
};

template<typename... Args>
  requires Addable<Args...>
auto Add(Args&&... args)
{
  return (... + args);
}

// #A Class template stub to create the different needed
// properties
template<bool nexcept, bool operatorPlus, bool validReturnType>
struct Stub {
  // #B Operator plus with controlled noexcept can be enabled
  Stub& operator+(const Stub& rhs) noexcept(nexcept)
    requires(operatorPlus && validReturnType)
  {
    return *this;
  }

  // #C Operator plus with invalid return type
  int operator+(const Stub& rhs) noexcept(nexcept)
    requires(operatorPlus && not validReturnType)
  {
    return {};
  }
};

// #D Create the different stubs from the class template
using NoAdd               = Stub<true, false, true>;
using ValidClass          = Stub<true, true, true>;
using NotNoexcept         = Stub<false, true, true>;
using DifferentReturnType = Stub<true, true, false>;

template<typename... Args>
concept TestAdd =
  requires  // #A Define a variadic concept as helper
{
  Add(std::declval<Args>()...);  // #B Use declval to call add
                                 // with the given types
};

// #A Assert that  mixed types are not allowed
static_assert(not Addable<int, double>);

// #B Assert that Add is used with at least two parameters
static_assert(not Addable<int>);

// #C Assert that type has operator+
static_assert(Addable<int, int>);
static_assert(Addable<ValidClass, ValidClass>);
static_assert(not Addable<NoAdd, NoAdd>);

// #D Assert that operator+ is noexcept
static_assert(not Addable<NotNoexcept, NotNoexcept>);

// #E Assert that operator+ returns the same type
static_assert(
  not Addable<DifferentReturnType, DifferentReturnType>);

int main() {}