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

struct arena {
  void* Allocate(size_t size) noexcept;
  void  Deallocate(void* p, size_t size) noexcept;

  static arena* GetFromPtr(void* ptr, size_t size);
};

void* arena::Allocate(size_t sz) noexcept
{
  auto osz = sz;
  sz += sizeof(arena*);

  char* ptr = new char[sz];

  [[maybe_unused]] arena* a =
    reinterpret_cast<arena*>(ptr + osz);

  a = this;

  arena* b = reinterpret_cast<arena*>(ptr + osz);

  printf("custom alloc %zu  %p  %p  %p\n", osz, ptr, this, b);

  return ptr;
}

arena* arena::GetFromPtr(void* ptr, size_t sz)
{
  return reinterpret_cast<arena*>(static_cast<char*>(ptr) + sz);
}

void arena::Deallocate(void* ptr, size_t sz) noexcept
{
  printf("custom dealloc %zu  %p  %p\n", sz, ptr, this);
  delete[] static_cast<char*>(ptr);
}

template<typename T, typename G, bool InitialSuspend>
struct promise_type_base {
  T mValue;

  std::suspend_always yield_value(T value)
  {
    mValue = value;
    return {};
  }

  auto initial_suspend()
  {
    if constexpr(InitialSuspend) {
      return std::suspend_always{};
    } else {
      return std::suspend_never{};
    }
  }

  std::suspend_always final_suspend() noexcept { return {}; }
  G                   get_return_object() { return G{this}; };
  void                unhandled_exception();
  void                return_void() {}

  // #A Custom operator new
  template<typename... TheRest>
  void*
  operator new(size_t size, arena& a, TheRest&&...) noexcept
  {
    return a.Allocate(size);
  }

  // #B Custom operator delete
  void operator delete(void* ptr, size_t size)
  {
    arena::GetFromPtr(ptr, size)->Deallocate(ptr, size);
  }

  static auto get_return_object_on_allocation_failure()
  {
    return G{nullptr};
  }
};

template<typename T, typename G, bool InitialSuspend>
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

FSM Parse(
  arena&            a,
  DataStreamReader& stream)  // #A Pass the stream a parameter
{
  while(true) {
    byte        b = co_await stream;  // #B Await on the stream
    std::string frame{};

    if(ESC == b) {
      b = co_await stream;

      // not looking at a end/start sequence
      if(SOF != b) { continue; }

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

generator<byte> sender(arena& a, std::vector<byte> fakeBytes)
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

  arena a1{};
  arena a2{};

  // #A Pass the arena to sender
  auto stream1 = sender(a1, std::move(fakeBytes1));

  DataStreamReader
       dr{};  // #B Create a DataStreamReader Awaitable
  auto p = Parse(a2, dr);  // #C Create the Parse coroutine and
                           // pass the DataStreamReader

  for(const auto& b : stream1) {
    dr.set(b);  // #D Send the new byte to the waiting
                // DataStreamReader

    if(const auto& res = p(); res.length()) {
      HandleFrame(res);
    }
  }

  auto stream2 = sender(
    a1,
    std::move(
      fakeBytes2));  // #E Simulate a second network stream

  for(const auto& b : stream2) {
    dr.set(b);  // #F We still use the former dr and p and feed
                // it with new bytes

    if(const auto& res = p(); res.length()) {
      HandleFrame(res);
    }
  }
}