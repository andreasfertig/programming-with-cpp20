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
  ReturnCode(T t, int e)
  : returnCode{t}
  , err{e}
  {}

  auto GetReturnCode() const { return returnCode; }
  int  GetErrno() const { return err; }

private:
  T   returnCode;
  int err;
};

auto Open(std::string_view fileName)
{
  // #B Works without specifying a type
  return ReturnCode{open(fileName.data()), errno};
}

int main()
{
  [[maybe_unused]] const auto result = Open("myfile.txt");
}