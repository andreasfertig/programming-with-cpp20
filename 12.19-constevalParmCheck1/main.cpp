// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <string_view>
#include <utility>

#include <version>

#if not defined(_MSC_VER)
#  if not(__cpp_lib_constexpr_string > 201911)
class string {
public:
  constexpr string() = default;
  constexpr string(const char& c) { append(&c, 1); }
  constexpr string(const string& s) { append(s.data(), s.size()); }
  constexpr string& operator=(const string& s)
  {
    reset();
    append(s.data(), s.size());
    return *this;
  }

  constexpr string(string&& s) noexcept
  : _data{std::exchange(s._data, nullptr)}
  , _length{s._length}
  {}

  constexpr string& operator=(string&& s) noexcept
  {
    std::exchange(_data, s._data);
    _length = s._length;
    return *this;
  }

  // a regular std::string is convertible to a string_view or better
  // there is a string_view ctor for a std::string. Make that work
  constexpr operator std::string_view() const noexcept
  {
    return {_data, _length};
  }

  constexpr string(std::string_view d) { append(d.data(), d.size()); }
  constexpr ~string() noexcept { reset(); }

  constexpr string& append(std::string_view d)
  {
    return append(d.data(), d.size());
  }
  constexpr string& append(const string& s)
  {
    return append(s.data(), s.size());
  }
  constexpr string& append(const char* d, std::size_t len)
  {
    const std::size_t needNt{(len && (d[len - 1] != '\0')) ? 1u : 0u};

    char* tmp = new char[_length + len + needNt]{};
    std::copy_n(_data, _length, tmp);
    std::copy_n(d, len, tmp + _length);
    _length += len;

    delete[] _data;

    _data = tmp;

    return *this;
  }

  constexpr bool operator==(const string& s) const noexcept
  {
    return std::equal(_data, _data + _length, s._data);
  }

  constexpr char*       data() { return _data; }
  constexpr char*       data() const { return _data; }
  constexpr std::size_t size() const { return _length; }

private:
  char*       _data{};
  std::size_t _length{};

  constexpr void reset()
  {
    delete[] _data;
    _data   = nullptr;
    _length = 0;
  }
};
#  else
#    include <string>
using std::string;
#  endif

constexpr string itoa(int num, int base = 10)
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

  for(auto i{rv.size()}; i > 0; --i) {
    ret.append(rv.substr(i - 1, 1));
  }

  return ret;
}

template<typename T, class... Args>
constexpr void Formatter(string&          buffer,
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

  if constexpr(sizeof...(Args) > 0) {
    Formatter<Args...>(buffer, v, args...);
  }
}

template<class... Args>
struct basic_format_string {
  std::string_view str;  // #A Holds the actual format string

  template<class T>
  requires std::is_convertible_v<const T&, std::string_view>
  consteval basic_format_string(
    const T& s)  // #B A consteval constructor
  : str{s}
  {
    string out{};
    // #C Use the regular format function
    Formatter(out, str, Args{}...);
  }
};

// #D Make constructor working without arguments
template<class... Args>
using format_string =
  basic_format_string<std::type_identity_t<Args>...>;

template<class... Args>
string format(format_string<Args...> fmt, const Args&... args);

template<class... Args>
string format(format_string<Args...> fmt, const Args&... args)
{
  string out{};
  Formatter(out, fmt.str, args...);

  return out;
}

void Use()
{
  auto str = format("ds", 12457, " hello");

  printf("'%s'", str.data());
}
#else
void Use()
{
#  pragma message("not supported")
}
#endif

int main()
{
  Use();
}