// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <vector>

// #A Type is neither copy nor movable
struct NonCopyableOrMoveable {
  NonCopyableOrMoveable() = default;
  NonCopyableOrMoveable(const NonCopyableOrMoveable&) =
    delete;
  NonCopyableOrMoveable(NonCopyableOrMoveable&&) = delete;
  NonCopyableOrMoveable&
  operator=(const NonCopyableOrMoveable&) = delete;
  NonCopyableOrMoveable&
  operator=(NonCopyableOrMoveable&&) = delete;
  ~NonCopyableOrMoveable()           = default;
};

NonCopyableOrMoveable RVO()
{
  return {};  // #B This is where RVO happens
}

void Use()
{
  // #C The return-object is created directly at  myValue
  auto myValue = RVO();
}

int main()
{
  Use();
}