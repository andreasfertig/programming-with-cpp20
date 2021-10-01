// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>)
#  include <format>
#  include <iomanip>
#  include <iostream>
#  include <locale>
#  include <string>
#  include <vector>

class Share {
  std::string mName;
  double      mPrice;
  double      mPriceDelta;

public:
  Share(std::string name, double price, double priceDelta)
  : mName{name}
  , mPrice{price}
  , mPriceDelta{priceDelta}
  {}

  auto name() const { return mName; }
  auto price() const { return mPrice; }
  auto priceDelta() const { return mPriceDelta; }
};

std::vector<Share> GetShares()
{
  return {{"Apple", 119.26, 23.4},
          {"Alphabet", 1'777.02, -10.21},
          {"Facebook", 276.95, 5.32},
          {"Tesla", 408.5, -31.5}};
}

void WithStdFormat()
{
  for(const auto& share : GetShares()) {
    std::cout << std::format("{:10} {:>8.2f}€ {:>+8.2f}€\n",
                             share.name(),
                             share.price(),
                             share.priceDelta());
  }
}

void WithStdFormatUseArgumentIndex()
{
  for(const auto& share : GetShares()) {
    std::cout << std::format("{1:10} {2:>8.2f}{0} {3:>+8.2f}{0}\n",
                             "€",
                             share.name(),
                             share.price(),
                             share.priceDelta());
  }
}

int main()
{
  WithStdFormat();
  WithStdFormatUseArgumentIndex();
}

#else
int main()
{
#  pragma message("not supported")
}
#endif