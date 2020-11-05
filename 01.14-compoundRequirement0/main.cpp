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
requires 
requires(Args... args)
{
  (... + args);                  // #A Check that arg provides +
  requires are_same_v<Args...>;  // #B Check all types are the same
  requires sizeof...(Args) > 1;  // #C Check that the pack contains at least two elements

  // #D Assert that ...+arg is noexcept and the return type is the same as the first argument type

  { (... + args) } noexcept -> same_as<first_arg_t<Args...>>;
}


auto add(Args&&... args)
{
  return (... + args);
}

class Rational {
public:
  Rational(int numerator = 0, int denominator = 1)
  : mNumerator(numerator)
  , mDenominator(denominator)
  {}

  Rational& operator+(const Rational& rhs) noexcept;

  // other operators

  int Numerator() const { return mNumerator; }
  int Denominator() const { return mDenominator; }

private:
  int mNumerator;
  int mDenominator;
};


Rational& Rational::operator+(const Rational& rhs) noexcept
{
  // dummy implementation
  mDenominator *= rhs.Denominator();
  mNumerator *= rhs.Numerator();

  return *this;
}


int main()
{
#  if not (defined(__GNUC__) && !defined(__clang__))
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2, 5));

  auto a = add(Rational{3, 4}, Rational{4, 4}, Rational{5, 4});
  printf("%d/%d\n", a.Numerator(), a.Denominator());
#  else
#    pragma message("not supported")
  return 1;
#  endif
}