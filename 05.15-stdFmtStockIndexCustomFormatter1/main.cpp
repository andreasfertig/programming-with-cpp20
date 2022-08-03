// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <format>
#  include <iomanip>
#  include <iostream>
#  include <locale>
#  include <string>
#  include <string_view>
#  include <vector>

using namespace std::literals;

class StockIndex {
  std::string mName{};
  double      mLastPoints{};
  double      mPoints{};

public:
  StockIndex(std::string name)
  : mName{name}
  {}

  const std::string& name() const { return mName; }

  void setPoints(double points)
  {
    mLastPoints = mPoints;
    mPoints     = points;
  }

  double points() const { return mPoints; }

  double pointsDiff() const { return mPoints - mLastPoints; }

  double pointsPercent() const
  {
    if(0.0 == mLastPoints) { return 0.0; }
    return (mPoints - mLastPoints) / mLastPoints * 100.0;
  }
};

std::vector<StockIndex> GetIndices()
{
  StockIndex dax{"DAX"};
  dax.setPoints(13'052.95);
  dax.setPoints(13'108.50);

  StockIndex dow{"Dow"};
  dow.setPoints(29'080.17);
  dow.setPoints(29'290.00);

  StockIndex sp{"S&P 500"};
  sp.setPoints(3'537.01);
  sp.setPoints(3'561.50);

  return {dax, dow, sp};
}

template<>
struct std::formatter<StockIndex> {
  enum class IndexFormat { Normal, Short, WithPlus };

  IndexFormat indexFormat{IndexFormat::Normal};

  constexpr auto parse(format_parse_context& ctx)
  {
    auto it  = ctx.begin();
    auto end = ctx.end();

    if((it != end) && (*it == 's')) {
      indexFormat = IndexFormat::Short;
      ++it;
    } else if((it != end) && (*it == 'p')) {
      indexFormat = IndexFormat::WithPlus;
      ++it;
    }

    // #A Check if reached the end of the range
    if(it != end && *it != '}') {
      throw format_error("invalid format");
    }

    // #B Return an iterator past the end of the parsed  range
    return it;
  }

  auto format(const StockIndex& index, std::format_context& ctx)
  {
    if(IndexFormat::Short == indexFormat) {
      return std::format_to(ctx.out(),
                            "{:10} {:>8.2f}"sv,
                            index.name(),
                            index.points());
    } else {
      const auto fmt{
        (IndexFormat::WithPlus == indexFormat)
          ? "{:10} {:>8.2f}  {: >+7.2f}  {:+.2f}%"sv
          : "{:10} {:>8.2f}  {:>6.2f}  {:.2f}%"sv};

      return std::vformat_to(
        ctx.out(),
        fmt,
        std::make_format_args(index.name(),
                              index.points(),
                              index.pointsDiff(),
                              index.pointsPercent()));
    }
  }
};

int main()
{
  for(const auto& index : GetIndices()) {
    std::cout << std::format("{}\n", index);
  }

  for(const auto& index : GetIndices()) {
    std::cout << std::format("{:s}\n", index);
  }

  for(const auto& index : GetIndices()) {
    std::cout << std::format("{:p}\n", index);
  }
}

#else
int main()
{
#  pragma message("not supported")
}
#endif