// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <functional>

#include <concepts>
#include <cstdio>
#include <mutex>
#include <type_traits>

std::mutex globalOsMutex;

void DoLocked(std::invocable auto&& f)
{
  std::lock_guard lck{globalOsMutex};

  f();
}

int main()
{
  DoLocked([] { puts("hello"); });
}