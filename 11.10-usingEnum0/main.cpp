// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <string_view>

enum class Permission {
  Read = 0,
  Write,
  Execute,
};

constexpr std::string_view to_string(Permission permission)
{
  switch(permission) {
    case Permission::Read: return "Read";
    case Permission::Write: return "Write";
    case Permission::Execute: return "Execute";
  }

  return "unknown";
}

int main()
{
  const Permission permission{Permission::Read};

  const auto permissionStr{to_string(permission)};

  printf("%s\n", permissionStr.data());
}