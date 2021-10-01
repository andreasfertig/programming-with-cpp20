// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<ranges>)
#  include <algorithm>
#  include <cassert>
#  include <iostream>
#  include <ranges>
#  include <string>
#  include <vector>

namespace rv = std::ranges::views;

template<std::ranges::view R>
requires std::ranges::view<R>
class custom_take_view : public std::ranges::view_interface<custom_take_view<R>> {
private:
  R                                  base_{};
  std::ranges::range_difference_t<R> count_{};

public:
  custom_take_view() = default;

  constexpr custom_take_view(R base, std::ranges::range_difference_t<R> count)
  : base_{std::move(base)}
  , count_{count}
  {}

  constexpr R base() const& { return base_; }
  constexpr R base() && { return std::move(base_); }

  constexpr auto begin() { return std::ranges::begin(base_); }
  constexpr auto end() { return std::ranges::next(std::ranges::begin(base_), count_); }
};

template<std::ranges::range R>
custom_take_view(R&& base, std::ranges::range_difference_t<R>)
  -> custom_take_view<std::ranges::views::all_t<R>>;

namespace details {
  template<std::integral T>
  struct custom_take_range_adaptor_closure {
    T count_;
    constexpr custom_take_range_adaptor_closure(T count)
    : count_{count}
    {}

    template<std::ranges::viewable_range R>
    constexpr auto operator()(R&& r) const
    {
      return custom_take_view(std::forward<R>(r), count_);
    }
  };

  struct custom_take_range_adaptor {
    template<typename... Args>
    constexpr auto operator()(Args&&... args)
    {
      if constexpr(sizeof...(Args) == 1) {
        return custom_take_range_adaptor_closure{args...};
      } else {
        return custom_take_view{std::forward<Args>(args)...};
      }
    }
  };

  template<std::ranges::viewable_range R, std::invocable<R> Adaptor>
  constexpr auto operator|(R&& r, const Adaptor& a)
  {
    return a(std::forward<R>(r));
  }

}  // namespace details

namespace views {
  inline details::custom_take_range_adaptor custom_take;
}

int main()
{
  auto is_even = [](int const n) { return n % 2 == 0; };

  std::vector<int> n{2, 3, 5, 6, 7, 8, 9};
  auto             v = n | rv::filter(is_even) | views::custom_take(2);
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
}

#else

int main()
{
#  pragma message("not supported")
}

#endif