// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cerrno>
#include <cstdio>
#include <version>

int open(const char*)
{
  return 1;
}

#if(__cpp_deduction_guides >= 201907L)

template<typename T>
struct ReturnCode {
  T   returnCode;
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
#else
int main()
{
#  pragma message("not supported")
}
#endif