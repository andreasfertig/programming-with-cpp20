// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cassert>
#include <coroutine>
#include <cstdio>
#include <functional>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>
#include <version>

using std::byte;
std::byte operator""_B(char c)
{
  return static_cast<byte>(c);
}
std::byte operator""_B(unsigned long long c)
{
  return static_cast<byte>(c);
}

template<typename T, typename G, 
         typename... Bases>  // #A Allow multiple bases for awaiter
struct promise_type_base : public Bases... {
  T mValue;

  auto yield_value(T value)
  {
    mValue = value;
    return std::suspend_always{};
  }

  G get_return_object() { return G{this}; };

  std::suspend_always initial_suspend() { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  void                return_void() {}
  void                unhandled_exception() 
                      { std::terminate(); }
};


namespace coro_iterator {
  template<typename PT>
  struct iterator {
    using coro_handle = std::coroutine_handle<PT>;

    coro_handle mCoroHdl{nullptr};
    bool        mDone{true};

    using RetType = decltype(mCoroHdl.promise().mValue);

    void resume()
    {
      mCoroHdl.resume();
      mDone = mCoroHdl.done();
    }

    iterator() = default;

    iterator(coro_handle hco)
    : mCoroHdl{hco}
    {
      resume();
    }

    iterator& operator++()
    {
      resume();
      return *this;
    }

    bool operator==(const iterator& o) const { return mDone == o.mDone; }

    const RetType& operator*() const { return mCoroHdl.promise().mValue; }
    const RetType* operator->() const { return &(operator*()); }
  };
}  // namespace coro_iterator


template<typename T>
struct awaitable_promise_type_base {
  std::optional<T> mRecentSignal;

  struct awaiter {
    std::optional<T>& mRecentSignal;

    bool await_ready() const { return mRecentSignal.has_value(); }
    void await_suspend(std::coroutine_handle<>) {}

    T await_resume()
    {
      assert(mRecentSignal.has_value());
      auto tmp = *mRecentSignal;
      mRecentSignal.reset();
      return tmp;
    }
  };

  [[nodiscard]] awaiter await_transform(T) 
  { return awaiter{mRecentSignal}; }
};


template<typename T, typename U>
struct [[nodiscard]] async_generator
{
  using promise_type = promise_type_base<T, 
                                async_generator, 
                                awaitable_promise_type_base<U>>;
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;

  T operator()()
  {
    // #A the move also clears the mValue of the promise
    auto tmp{std::move(mCoroHdl.promise().mValue)};

    // #B but we have to set it to a defined state
    mCoroHdl.promise().mValue.clear();

    return tmp;
  }

  void SendSignal(U signal)
  {
    mCoroHdl.promise().mRecentSignal = signal;
    if(not mCoroHdl.done()) { mCoroHdl.resume(); }
  }

  async_generator(const async_generator&) = delete;
  async_generator(async_generator&& rhs)
  : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)}
  {}

  ~async_generator()
  {
    if(mCoroHdl) { mCoroHdl.destroy(); }
  }

private:
  friend promise_type;  // #C As the default ctor is private G needs to be a friend
  explicit async_generator(promise_type* p)
  : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {}

  PromiseTypeHandle mCoroHdl;
};


template<typename T>
struct generator {
  using promise_type      = promise_type_base<T, generator>;
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;
  using iterator          = coro_iterator::iterator<promise_type>;

  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs)
  : mCoroHdl(rhs.mCoroHdl)
  {
    rhs.mCoroHdl = nullptr;
  }

  ~generator()
  {
    if(mCoroHdl) { mCoroHdl.destroy(); }
  }

private:
  friend promise_type;  // #A As the default ctor is private G needs to be a friend
  explicit generator(promise_type* p)
  : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {}

  PromiseTypeHandle mCoroHdl;
};


using FSM = async_generator<std::string, byte>;


static const byte ESC{'H'};
static const byte SOF{0x10};


FSM Parse()
{
  while(true) {
    byte b = co_await byte{};
    if(ESC != b) { continue; }

    b = co_await byte{};
    if(SOF != b) { continue; }  // #A  not looking at a start sequence

    std::string frame{};
    while(true) {  // #B capture the full frame
      b = co_await byte{};

      if(ESC == b) {
        // #C skip this byte and look at the next one
        b = co_await byte{};

        if(SOF == b) {
          co_yield frame;
          break;
        } else if(ESC != b) {  // #D out of sync
          break;
        }
      }

      frame += static_cast<char>(b);
    }
  }
}


generator<byte> sender(std::vector<byte> fakeBytes)
{
  for(const auto& b : fakeBytes) { co_yield b; }
}


void HandleFrame(const std::string& frame);

void ProcessStream(generator<byte>& stream, FSM& parse)
{
  for(const auto& b : stream) {
    // #A Send the new byte to the waiting Parse coroutine
    parse.SendSignal(b);  

    // #B Check whether we have a complete frame
    if(const auto& res = parse(); res.length()) { 
        HandleFrame(res); 
    }
  }
}



void HandleFrame(const std::string& frame)
{
  printf("%s\n", frame.c_str());
}

int main()
{
  std::vector<byte> fakeBytes1{
    0x70_B, ESC, SOF, ESC, 
    'H'_B, 'e'_B, 'l'_B, 'l'_B, 'o'_B, ESC, SOF, 
    0x7_B, ESC, SOF};

// #A Simulate the first network stream
auto stream1 = sender(std::move(fakeBytes1));  

// #B Create the Parse coroutine and store the handle in p
auto p = Parse();

ProcessStream(stream1, p);  // #C Process the bytes

// #D Simulate the reopening of the network stream
std::vector<byte> fakeBytes2{
    'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B};

// #E Simulate a second network stream
auto stream2 = sender(std::move(fakeBytes2));

// #F We still use the former p and feed it with new bytes
ProcessStream(stream2, p);

}