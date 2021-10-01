// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if not defined(_MSC_VER)
#  include <array>
#  include <concepts>
#  include <cstdio>
#  include <queue>
#  include <type_traits>

template<typename T>
concept ByteLikeType = std::is_same_v<char, T> || std::is_same_v<unsigned char, T> ||
  std::is_same_v<const char, T> || std::is_same_v<const unsigned char, T>;

// #A Make value_type easily accessible
template<typename T>
using value_type_t = typename std::remove_reference_t<T>::value_type;

// #B A constexpr function to obtain the size
template<typename T>
constexpr auto ExtractSize(T t = {})  // #C Default parameter

{
  return t.size();  // #D Call the size function of the container
}

template<typename T>
concept SmallBuffer = ExtractSize<std::remove_reference_t<T>>()
<= 16 &&                          // #A Constrain the size
  ByteLikeType<value_type_t<T>>;  // #B Ensure the value_type is byte-like

template<typename T>
concept LargeBuffer = not SmallBuffer<T> &&           // #C Not a SmallBuffer
                      ByteLikeType<value_type_t<T>>;  // #D But still a ByteLikeType

void Send(SmallBuffer auto&& buffer);
void Send(LargeBuffer auto&& buffer);

void Send(SmallBuffer auto&& buffer)
{
  // same as before
}

void Send(LargeBuffer auto&& buffer)
{
  // same as before
}

using AckType = std::array<char, 16>;

template<typename T>
using TimedQueue = std::queue<T>;

static TimedQueue<AckType> gAckQueue{};

void send(const char* data, const size_t len) {}

template<typename T>
void PushToAckQueue(T& buffer)
{
  gAckQueue.push(buffer);
}

void FlushAckQueue()
{
  while(gAckQueue.size()) {
    const auto e = gAckQueue.front();
    send(e.data(), e.size());
  }
}

namespace implementationWithRequires {
  template<typename T>
  requires SmallBuffer<T>
  void Send(T&& buffer)
  {
    if(gAckQueue.size() > 10) {
      FlushAckQueue();

    } else {
      PushToAckQueue(buffer);
    }
  }

  template<typename T>
  requires LargeBuffer<T>
  void Send(T&& buffer) { send(buffer.data(), buffer.size()); }

  void CallingSendWithRequires()
  {
    std::array<char, 16>  ackData{};
    std::array<char, 100> payloadData{};

    Send(ackData);
    Send(payloadData);
  }
}  // namespace implementationWithRequires

namespace implementationWithTypeConstraint {
  template<SmallBuffer T>
  void Send(T&& buffer)
  {
    // same as before
  }

  template<LargeBuffer T>
  void Send(T&& buffer)
  {
    // same as before
  }

}  // namespace implementationWithTypeConstraint

namespace implementationWithTrailingRequires {
  template<typename T>
  void Send(T&& buffer) requires SmallBuffer<T>
  {
    // same as before
  }

  template<typename T>
  void Send(T&& buffer) requires LargeBuffer<T>
  {
    // same as before
  }

}  // namespace implementationWithTrailingRequires

template<typename T, auto N>
struct array {
  using value_type = T;
  T data[N];

  constexpr auto size() const { return N; }
};

int main()
{
  std::array<char, 16>  ackData{};
  std::array<char, 100> payloadData{};

  Send(ackData);
  Send(payloadData);

  // Custom array
  {
    array<char, 10>  ackData{};
    array<char, 100> payloadData{};

    Send(ackData);
    Send(payloadData);
  }

  implementationWithRequires::CallingSendWithRequires();
}
#else
int main()
{
#  pragma message("not supported")
}
#endif