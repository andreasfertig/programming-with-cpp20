// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <format>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

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

void WithPrintf()
{
  for(const auto& index : GetIndices()) {
    printf("%-10s %8.2lf  %6.2lf  %4.2lf%%\n",
           index.name().c_str(),
           index.points(),
           index.pointsDiff(),
           index.pointsPercent());
  }
}

void WithIostreamAdvanced()
{
  for(const auto& index : GetIndices()) {
    std::cout << std::fixed;
    // #A We need <iomanip> for this
    std::cout << std::setprecision(2);

    std::cout << std::setw(10) << std::left << index.name()
              << "  " << std::setw(8) << std::right
              << index.points() << "  " << std::setw(6)
              << index.pointsDiff() << " "
              << index.pointsPercent() << '%' << '\n';
  }
}

std::ostream& operator<<(std::ostream&     os,
                         const StockIndex& index)
{
  os << std::fixed;
  os << std::setprecision(2);

  os << std::setw(10) << std::left << index.name() << "  "
     << std::setw(8) << std::right << index.points() << "  "
     << std::setw(6) << index.pointsDiff() << " "
     << index.pointsPercent() << '%' << '\n';

  return os;
}

void WithIostreamOperator()
{
  for(const auto& index : GetIndices()) { std::cout << index; }
}

namespace withLocale {
  // #  include "withIostreamOperatorLocale.cpp"
}

void WithStdFormat()
{
  for(const auto& index : GetIndices()) {
    std::cout << std::format(
      "{:10}  {:>8.2f}  {:>6.2f} {:.2f}%\n",
      index.name(),
      index.points(),
      index.pointsDiff(),
      index.pointsPercent());
  }
}

int main()
{
  WithPrintf();
  std::cout << '\n';
  WithIostreamAdvanced();
  std::cout << '\n';

  double test = 3.1;
  std::cout << test << '\n';

  WithIostreamOperator();

  std::cout << '\n';
  WithStdFormat();
}