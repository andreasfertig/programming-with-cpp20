// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <type_traits>

template<typename T, typename U>
concept same_as =
  std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename... Args>
concept Addable = requires(T arg)
{
  arg + arg;
};

template<typename... Args>
concept PackHasElements = sizeof...(Args) > 0;

template<typename T, typename... Args>
concept AddReturnsSameType = requires(T arg)
{
  {
    arg + arg
  }
  noexcept->same_as<T>;
};

template<typename T>
concept ClassWithType = not std::is_class_v<T> || requires
{
  typename T::type;
};


template<typename T, typename... Args>
requires Addable<T, Args...> && are_same_v<T, Args...> 
         && PackHasElements<Args...> && AddReturnsSameType<T>
         && ClassWithType<T>
auto add(T&& arg, Args&&... args)
// ...

{
  return (arg + ... + args);
}

template<typename T>
class Rational {
public:
  using type = T;

  constexpr Rational(T numerator = 0, T denominator = 1)
  : mNumerator(numerator)
  , mDenominator(denominator)
  {}

  constexpr Rational& operator+(const Rational& rhs) noexcept;

  // other operators

  constexpr T Numerator() const { return mNumerator; }
  constexpr T Denominator() const { return mDenominator; }

private:
  T mNumerator;
  T mDenominator;
};

template<typename T>
constexpr Rational<T>& Rational<T>::operator+(const Rational<T>& rhs) noexcept
{
  // dummy implementation
  mDenominator *= rhs.Denominator();
  mNumerator *= rhs.Numerator();

  return *this;
}



int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2, 5));

  using RationalInt = Rational<int>;

  auto a = add(RationalInt{3, 4}, RationalInt{4, 4}, RationalInt{5, 4});
  printf("%d/%d\n", a.Numerator(), a.Denominator());
}