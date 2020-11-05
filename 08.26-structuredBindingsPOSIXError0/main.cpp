// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cerrno>
#include <cstdio>

int open(const char*)
{
  return 1;
}

struct ReturnCode {
  int returnCode;
  int err;
};

auto Open(const char* fileName)
{
  return ReturnCode{open(fileName), errno};
}

int main()
{
  auto [code, err] = Open("myfile.txt");

  printf("errno: %d, value: %d\n", err, code);
}