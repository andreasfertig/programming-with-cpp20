// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cerrno>
#include <cstdio>
#include <string_view>

int open(const char*)
{
  return 1;
}

template<typename T>
struct ReturnCode {
  T   returnCode;  // #A Make the return code's type generic
  int err;
};

auto Open(std::string_view fileName)
{
  // #B We need to specify the type of the template parameter
  return ReturnCode<int>{open(fileName.data()), errno};
}

int main()
{
  auto [code, err] = Open("myfile.txt");

  printf("errno: %d, value: %d\n", err, code);
}