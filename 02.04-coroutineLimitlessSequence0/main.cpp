// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <version>

#if __has_include(<experimental/coroutine>)
#  include <experimental/coroutine>

namespace std {
  using namespace std::experimental;
}
#elif __has_include(<coroutine>)
#if __has_include(<experimental/coroutine>)
#include <experimental/coroutine>
namespace std { using namespace std::experimental; }
#elif __has_include(<coroutine>)
#include <coroutine>
#endif
#else
#  pragma message("not supported")
#endif

#include <cstdio>
#include <exception>
#include <utility>

template<typename T, typename G>
struct promise_type_base {
  T mValue;  // #A The value yielded or returned from a coroutine

  auto yield_value(T value)  // #B Invoked by co_yield or co_return
  {
    mValue = std::move(value);  // #C Store the yielded value for access outside the coroutine

    return std::suspend_always{};  // #D Suspend the coroutine here
  }

  G get_return_object() { return G{this}; };  // #E Return generator

  std::suspend_always initial_suspend() { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  void                return_void() {}
  void                unhandled_exception() { std::terminate(); }
  static auto get_return_object_on_allocation_failure() { return G{nullptr}; }
};


namespace coro_iterator {
  template<typename PT>
  struct iterator {
    std::coroutine_handle<PT> mCoroHdl{nullptr};

    void resume()
    {
      if(not mCoroHdl.done()) { mCoroHdl.resume(); }
    }

    iterator() = default;
    iterator(std::coroutine_handle<PT> hco)
    : mCoroHdl{hco}
    {
      resume();
    }

    void        operator++() { resume(); }
    bool        operator==(const iterator&) const { return mCoroHdl.done(); }
    const auto& operator*() const { return mCoroHdl.promise().mValue; }
  };
}  // namespace coro_iterator


template<typename T>
struct generator {
  using promise_type =
    promise_type_base<T, generator>;  // #A The PromiseType
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;

  // #B Make the generator iterable
  using iterator = coro_iterator::iterator<promise_type>;
  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs)
  : mCoroHdl(std::exchange(rhs.mCoroHdl, nullptr))
  {}

  ~generator()
  {
    // #C We have to maintain the life-time of the coroutine
    if(mCoroHdl) { mCoroHdl.destroy(); }
  }

private:
  friend promise_type;  // #D As the default ctor is private promise_type needs to be a friend

  explicit generator(promise_type* p)
  : mCoroHdl{PromiseTypeHandle::from_promise(*p)}
  {}

  PromiseTypeHandle mCoroHdl;  // #E The coroutine handle
};


using IntGenerator = generator<int>;

void UseCounterValue(int i);

IntGenerator  // #A Returning a coroutine object
counter(int start, int end)
{
  while(start < end) {
    co_yield start;  // #B Yielding a value and giving control back to the  caller
    ++start;
  }
}

void UseCounter()
{
  auto g = counter(1, 5);

  // #C This sequence runs from 1 to 5
  for(auto i : g) { UseCounterValue(i); }
}



void UseCounterValue(int i)
{
  printf("%d\n", i);
}

int main()
{
  UseCounter();
}