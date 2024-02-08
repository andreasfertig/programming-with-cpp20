// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

template<typename T>
concept SupportsValidation = requires(T t) { t.validate(); };

template<typename T>
void Send(const T& data)
{
  if constexpr(SupportsValidation<T>) { data.validate(); }

  // actual code sending the data
}

class ComplexType {
public:
  void validate() const;
};

class SimpleType {};

void ComplexType::validate() const
{
  // provide a validation implementation here
}

static_assert(SupportsValidation<ComplexType>);
static_assert(not SupportsValidation<SimpleType>);

int main()
{
  ComplexType a{};
  SimpleType  b{};

  Send(a);
  Send(b);
}