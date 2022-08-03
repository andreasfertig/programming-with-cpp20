// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cassert>
#include <coroutine>
#include <cstdio>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>
#include <version>

using namespace std::literals;

using std::byte;
std::byte operator""_B(char c)
{
  return static_cast<byte>(c);
}
std::byte operator""_B(unsigned long long c)
{
  return static_cast<byte>(c);
}

enum class Ex {
  None,
  ParseBegin,
  ParseWhileRunning,
  InitialSuspend,
  YieldValue,
  GetReturnObject,
};

static Ex  ex{Ex::None};
static int rethrow = 1;

void ThrowIf(const Ex v, std::string name)
{
  if(v == ex) { throw std::runtime_error(name); }
}

template<typename T, typename G, bool InitialSuspend>
struct promise_type_base {
  T mValue;

  std::suspend_always yield_value(T value)
  {
    ThrowIf(Ex::YieldValue, "yield_value");
    mValue = value;
    return {};
  }

  auto initial_suspend()
  {
    ThrowIf(Ex::InitialSuspend, "initial_suspend");
    if constexpr(InitialSuspend) {
      return std::suspend_always{};
    } else {
      return std::suspend_never{};
    }
  }

  std::suspend_always final_suspend() noexcept
  {
    printf("final_suspend\n");
    return {};
  }
  G get_return_object()
  {
    printf("get_return_object\n");
    ThrowIf(Ex::GetReturnObject, "get_return_object");

    return G{this};
  };

  void unhandled_exception()
  {
    printf("unhandled_exception\n");
    if(rethrow) {
      if(2 == rethrow) {
        auto exceptionPtr = std::current_exception();
        try {
          if(exceptionPtr) {
            std::rethrow_exception(exceptionPtr);
          }
        } catch(const std::exception& e) {
          std::cout << "Caught exception \"" << e.what()
                    << "\"\n";
        }
      } else {
        throw;
      }
    } else {
      printf("do nothing\n");
    }
  }

  void return_void() {}
};

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

template<typename T, bool IntialSuspend = true>  // #A New NTTP
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
    // use swap for a potential move and defined cleared state
    std::swap(tmp, mCoroHdl.promise().mValue);

    return tmp;
  }

private:
  friend promise_type;  // #A As the default ctor is private we
                        // G needs to be a friend
  explicit generator(promise_type* p)
  : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {}

protected:
  PromiseTypeHandle mCoroHdl;
};

class DataStreamReader  // #A Awaitable
{
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
      // #D Stash the handle of the awaiting coroutine.
      mCoroHdl = coroHdl;
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

FSM Parse(DataStreamReader& stream)
{
  ThrowIf(Ex::ParseBegin, "ParseBegin");

  while(true) {
    byte        b = co_await stream;
    std::string frame{};

    if(ESC == b) {
      b = co_await stream;

      // not looking at a end/start sequence
      if(SOF != b) { continue; }

      ThrowIf(Ex::ParseWhileRunning, "ParseWhileRunning");

      // capture the full frame
      while(true) {
        b = co_await stream;

        if(ESC == b) {
          // skip this byte and look at the next one
          b = co_await stream;

          if(SOF == b) {
            co_yield frame;
            break;
          } else if(ESC != b) {
            // out of sync
            break;
          }
        }

        frame += static_cast<char>(b);
      }
    }
  }
}

generator<byte> sender(std::vector<byte> fakeBytes)
{
  for(const auto& b : fakeBytes) { co_yield b; }
}

void HandleFrame(const std::string& frame);
void PrintException(std::runtime_error& rt);

void HandleFrame(const std::string& frame)
{
  printf("%s\n", frame.c_str());
}

void PrintException(std::runtime_error& rt)
{
  std::cout << "ex: " << rt.what() << '\n';
}

int main(int argc, char* argv[])
{

  if(argc > 2) {
    rethrow = atoi(argv[1]);

    if("ParseBegin"s == argv[2]) {
      ex = Ex::ParseBegin;
    } else if("ParseWhileRunning"s == argv[2]) {
      ex = Ex::ParseWhileRunning;
    } else if("InitialSuspend"s == argv[2]) {
      ex = Ex::InitialSuspend;
    } else if("YieldValue"s == argv[2]) {
      ex = Ex::YieldValue;
    } else if("GetReturnObject"s == argv[2]) {
      ex = Ex::GetReturnObject;
    }
  }

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

  try {  // #A Wrap it in a try-catch block
    auto stream1 = sender(std::move(fakeBytes1));

    DataStreamReader dr{};
    auto             p = Parse(dr);

    for(const auto& b : stream1) {
      dr.set(b);

      if(const auto& res = p(); res.length()) {
        HandleFrame(res);
      }
    }
    // #B Listen for a runtime error
  } catch(std::runtime_error& rt) {
    PrintException(rt);
  }
}