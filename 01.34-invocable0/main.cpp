// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <functional>
#include <mutex>
#include <type_traits>

std::mutex globalOsMutex;

template<typename T>
void DoLocked(T&& f)
{
  std::lock_guard lck{globalOsMutex};

  f();
}

int main()
{
  DoLocked([] { printf("hello\n"); });
}