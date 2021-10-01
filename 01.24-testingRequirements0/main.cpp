// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename U>
concept same_as =
  std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
struct first_arg {
  using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template<typename... Args>
requires requires(Args... args)
{
  (... + args);
  requires are_same_v<Args...>;
  requires sizeof...(Args) > 1;
  {
    (... + args)
  }
  noexcept->same_as<first_arg_t<Args...>>;
  requires not std::is_class_v<first_arg_t<Args...>> || requires
  {
    typename first_arg_t<Args...>::type;
  };
}
auto add(Args&&... args)
{
  return (... + args);
}

// #A Helper to either have a type in the class
namespace details {
  struct WithType {
    using type = int;
  };

  struct WithoutType {};
}  // namespace details

// #B Class template stub to create the different needed properties
template<bool NOEXCEPT,
         bool hasOperatorPlus,
         bool hasType,
         bool validReturnType>
class ObjectStub
: public std::conditional_t<
    hasType,
    details::WithType,
    details::WithoutType>  // #C Based on hasType select a base class
{
public:
  ObjectStub() = default;

  // #D Operator plus with controlled noexcept can be enabled
  ObjectStub& operator+(const ObjectStub& rhs) noexcept(NOEXCEPT) requires(
    hasOperatorPlus&& validReturnType)
  {
    return *this;
  }

  // #E Operator plus with invalid return type
  int operator+(const ObjectStub& rhs) noexcept(NOEXCEPT) requires(
    hasOperatorPlus && not validReturnType)
  {
    return 3;
  }
};

// #F Create the different stubs from the class template
using NoAdd               = ObjectStub<true, false, true, true>;
using ValidClass          = ObjectStub<true, true, true, true>;
using NotNoexcept         = ObjectStub<false, true, true, true>;
using WithoutType         = ObjectStub<true, true, false, true>;
using DifferentReturnType = ObjectStub<true, true, false, false>;


template<typename... Args>
concept Test = requires  // #A Define a variadic concept as helper
{
  add(std::declval<Args>()...);  // #B Use declval to call add with the given types
};


// #A Assert that type has operator+
static_assert(Test<int, int>);
static_assert(not Test<NoAdd, NoAdd>);

// #B Assert, that no mixed types are allowed
static_assert(not Test<int, double>);

// #C Assert that pack has at least one parameter
static_assert(not Test<int>);

// #D Assert that operator+ is noexcept
static_assert(not Test<NotNoexcept, NotNoexcept>);

// #E Assert that operator+ returns the same type
static_assert(not Test<DifferentReturnType, DifferentReturnType>);

// #F Assert that a valid class works
static_assert(Test<ValidClass, ValidClass>);

// #G Assert that there is a type present in a class type
static_assert(not Test<WithoutType, WithoutType>);


int main(){}