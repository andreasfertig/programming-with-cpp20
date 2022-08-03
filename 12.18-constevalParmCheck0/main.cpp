// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <string_view>

#include <version>

#include <string>
using std::string;

string itoa(int num, int base = 10)
{
  if(num == 0) { return {'0'}; }

  string value{};

  while(num > 0) {
    const char sub = static_cast<char>(num % base);
    num /= base;

    // lack of std::string receiving a char
    const char v = sub + '0';
    value.append(&v, 1);
  }

  // reverse
  string           ret{};
  std::string_view rv{value};

  for(auto i{rv.size()}; i > 0; --i) { ret.append(rv.substr(i - 1, 1)); }

  return ret;
}

template<typename T, class... Args>
void Formatter(string&          buffer,
               std::string_view v,
               const T&         t,
               const Args&... args)
{
  using PT = std::remove_cv_t<T>;

  if constexpr(std::is_same_v<int, PT>) {
    if('d' != v[0]) { throw int{3}; }
    buffer.append(itoa(t));

  } else if constexpr(std::is_convertible_v<PT, std::string_view>) {
    if('s' != v[0]) { throw int{4}; }
    buffer.append(t);

  } else {
    throw int{6};
  }

  v.remove_prefix(1);

  if constexpr(sizeof...(Args) > 0) { Formatter<Args...>(buffer, v, args...); }
}

template<class... Args>
string format(std::string_view fmt, const Args&... args);

template<class... Args>
string format(std::string_view fmt, const Args&... args)
{
  string out{};
  Formatter(out, fmt, args...);

  return out;
}

int main()
{
  auto str = format("ds", 12457, " hello");

  printf("'%s'", str.data());
}