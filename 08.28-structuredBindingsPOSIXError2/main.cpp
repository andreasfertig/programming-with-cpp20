// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cerrno>
#include <cstdio>

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

auto Open(const char* fileName)
{
  // #B Works without specifying a type
  return ReturnCode{open(fileName), errno};
}

int main()
{
  auto [code, err] = Open("myfile.txt");

  printf("errno: %d, value: %d\n", err, code);
}