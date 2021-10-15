// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>
#include <version>

#if(__cpp_nontype_template_args >= 201911) && not defined(__clang__)
template<double x>
struct A;  // #A A type which uses double as NTTP

// #B Different bit pattern  results in different type
static_assert(not std::is_same_v<A<+0.6 - 0.2>, A<0.4>>);

// #C Different bit pattern  results in different type
static_assert(not std::is_same_v<A<+0.0>, A<-0.0>>);

static_assert(+0.0 == -0.0);  // #D IEEE 754 says they are equal

static_assert(std::is_same_v<A<0.1 + 0.1>, A<0.2>>);  // #E Same bit pattern

int main() {}
#else
int main()
{
#  pragma message("not supported")
}
#endif