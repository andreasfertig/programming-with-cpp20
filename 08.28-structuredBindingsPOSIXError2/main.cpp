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
  T   returnCode;
  int err;
};

// #A Deduction guide
template<typename T>
ReturnCode(T, int) -> ReturnCode<T>;

auto Open(std::string_view fileName)
{
  // #B Works without specifying a type
  return ReturnCode{open(fileName.data()), errno};
}

int main()
{
  auto [code, err] = Open("myfile.txt");

  printf("errno: %d, value: %d\n", err, code);
}