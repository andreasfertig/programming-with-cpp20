// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename U>
concept same_as = std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename... Args>
requires requires(T arg)
{
  arg + arg;                        // #A Check that arg provides +
  requires are_same_v<T, Args...>;  // #B Check all types are the same
  requires sizeof...(Args) > 0;     // #C Check that the pack contains at least one parameter
  {
    arg + arg
  }
  noexcept->same_as<T>;  // #D Assert the properties of arg+arg
  typename T::type;      // #E Assert a type requirement, T has "type"
}

auto add(T&& arg, Args&&... args)
{
  return (arg + ... + args);
}

template<typename T>
class Rational {
public:
  using type = T;

  // same as before

  Rational(T numerator = 0, T denominator = 1)
  : mNumerator(numerator)
  , mDenominator(denominator)
  {}

  Rational& operator+(const Rational& rhs) noexcept;

  // other operators

  T Numerator() const { return mNumerator; }
  T Denominator() const { return mDenominator; }

private:
  T mNumerator;
  T mDenominator;
};

template<typename T>
Rational<T>& Rational<T>::operator+(const Rational<T>& rhs) noexcept
{
  // dummy implementation
  mDenominator *= rhs.Denominator();
  mNumerator *= rhs.Numerator();

  return *this;
}

int main()
{
  using RationalInt = Rational<int>;

  auto a = add(RationalInt{3, 4}, RationalInt{4, 4}, RationalInt{5, 4});
  printf("%d/%d\n", a.Numerator(), a.Denominator());
}