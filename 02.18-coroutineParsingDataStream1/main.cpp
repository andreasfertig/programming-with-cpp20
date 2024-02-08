// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cassert>
#include <coroutine>
#include <cstdio>
#include <functional>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
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

template<typename T,
         typename G,
         bool InitialSuspend>  // #A Control the initial suspend
struct promise_type_base {
  T mValue;

  std::suspend_always yield_value(T value)
  {
    mValue = value;
    return {};
  }
  auto initial_suspend()
  {
    if constexpr(InitialSuspend) {  // #B Either suspend always
                                    // or  never
      return std::suspend_always{};
    } else {
      return std::suspend_never{};
    }
  }

  std::suspend_always final_suspend() noexcept { return {}; }
  G                   get_return_object() { return G{this}; };
  void                unhandled_exception();
  void                return_void() {}
};

template<typename T,
         typename G,
         bool InitialSuspend>  // #A Control the initial suspend
void promise_type_base<T, G, InitialSuspend>::
  unhandled_exception()
{
  std::terminate();
}

namespace coro_iterator {
  template<typename PT>
  struct iterator {
    using coro_handle = std::coroutine_handle<PT>;

    coro_handle mCoroHdl{};

    using RetType = decltype(mCoroHdl.promise().mValue);

    void resume() { mCoroHdl.resume(); }

    iterator() = default;

    iterator(coro_handle hco)
    : mCoroHdl{hco}
    {
      resume();
    }

    void operator++() { resume(); }

    bool operator==(const iterator&) const
    {
      return mCoroHdl.done();
    }
    const RetType& operator*() const
    {
      return mCoroHdl.promise().mValue;
    }
  };
}  // namespace coro_iterator

template<typename T,
         bool IntialSuspend = true>  // #A New NTTP
struct generator {
  using promise_type =
    promise_type_base<T,
                      generator,
                      IntialSuspend>;  // #B Forward
                                       // IntialSuspend

  using PromiseTypeHandle = std::coroutine_handle<promise_type>;
  using iterator = coro_iterator::iterator<promise_type>;

  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs)
  : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)}
  {}

  ~generator()
  {
    if(mCoroHdl) { mCoroHdl.destroy(); }
  }

  T operator()()
  {
    T tmp{};
    // #C use swap for a potential move and defined cleared
    // state
    std::swap(tmp, mCoroHdl.promise().mValue);

    return tmp;
  }

private:
  // #D As the default ctor is private we G  needs to be a
  // friend
  friend promise_type;
  explicit generator(promise_type* p)
  : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {}

protected:
  PromiseTypeHandle mCoroHdl;
};

class DataStreamReader {  // #A Awaitable
public:
  DataStreamReader() = default;

  // #B Using DesDeMovA to disable copy and move operations
  DataStreamReader&
  operator=(DataStreamReader&&) noexcept = delete;

  struct Awaiter {  // #C Awaiter implementation
    Awaiter& operator=(Awaiter&&) noexcept = delete;
    Awaiter(DataStreamReader& event) noexcept
    : mEvent{event}
    {
      mEvent.mAwaiter = this;
    }

    bool await_ready() const noexcept
    {
      return mEvent.mData.has_value();
    }

    void await_suspend(std::coroutine_handle<> coroHdl) noexcept
    {
      mCoroHdl = coroHdl;  // #D Stash the handle of the
                           // awaiting  coroutine.
    }

    byte await_resume() noexcept
    {
      assert(mEvent.mData.has_value());
      return *std::exchange(mEvent.mData, std::nullopt);
    }

    void resume() { mCoroHdl.resume(); }

  private:
    DataStreamReader&       mEvent;
    std::coroutine_handle<> mCoroHdl{};
  };

  // #E Make DataStreamReader awaitable
  auto operator co_await() noexcept { return Awaiter{*this}; }

  void set(byte b)
  {
    mData.emplace(b);
    if(mAwaiter) { mAwaiter->resume(); }
  }

private:
  friend struct Awaiter;
  Awaiter*            mAwaiter{};
  std::optional<byte> mData{};
};

using FSM = generator<std::string, false>;

static const byte ESC{'H'};
static const byte SOF{0x10};

FSM Parse(
  DataStreamReader& stream)  // #A Pass the stream a parameter
{
  while(true) {
    byte b = co_await stream;  // #B Await on the stream
    if(ESC != b) { continue; }

    b = co_await stream;
    // #C not looking at a end or start sequence
    if(SOF != b) { continue; }

    std::string frame{};
    // #D capture the full frame
    while(true) {
      b = co_await stream;

      if(ESC == b) {
        // #E skip this byte and look at the next one
        b = co_await stream;

        if(SOF == b) {
          co_yield frame;
          break;
        } else if(ESC != b) {
          break;  // #F out of sync
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

void HandleFrame(const std::string& frame)
{
  printf("%s\n", frame.c_str());
}

int main()
{
  std::vector<byte> fakeBytes1{0x70_B,
                               ESC,
                               SOF,
                               ESC,
                               'H'_B,
                               'e'_B,
                               'l'_B,
                               'l'_B,
                               'o'_B,
                               ESC,
                               SOF,
                               0x7_B,
                               ESC,
                               SOF};

  std::vector<byte> fakeBytes2{
    'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B};

  auto stream1 = sender(std::move(fakeBytes1));

  DataStreamReader
       dr{};           // #A Create a DataStreamReader Awaitable
  auto p = Parse(dr);  // #B Create the Parse coroutine and pass
                       // the DataStreamReader

  for(const auto& b : stream1) {
    dr.set(b);  // #C Send the new byte to the waiting
                // DataStreamReader

    if(const auto& res = p(); res.length()) {
      HandleFrame(res);
    }
  }

  auto stream2 = sender(std::move(
    fakeBytes2));  // #D Simulate a second network stream

  for(const auto& b : stream2) {
    dr.set(b);  // #E We still use the former dr and p and feed
                // it with new bytes

    if(const auto& res = p(); res.length()) {
      HandleFrame(res);
    }
  }
}