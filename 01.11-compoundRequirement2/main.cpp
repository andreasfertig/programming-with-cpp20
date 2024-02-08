// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename U>
concept same_as =
  std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template<typename T, typename... Ts>
constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
struct first_arg {
  using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template<typename... Args> 
concept Addable = requires(Args... args)
{
  (... + args);
  requires are_same_v<Args...>; 
  requires sizeof...(Args) > 1;
  { (... + args) } noexcept -> same_as<first_arg_t<Args...>>;
}; 

template<typename... Args> 
requires Addable<Args...>
auto Add(Args&&... args) noexcept
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
  printf("%d\n", Add(2, 3, 4));

  printf("%d\n", Add(2, 5));

  auto a = Add(Rational{3, 4}, Rational{4, 4}, Rational{5, 4});
  printf("%d/%d\n", a.Numerator(), a.Denominator());
}