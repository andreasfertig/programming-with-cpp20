// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <string_view>

enum class Permission {
  Read = 0,
  Write,
  Execute,
};

#if __cpp_using_enum
constexpr std::string_view to_string(Permission permission)
{
  switch(permission) {
    using enum Permission;  // #A New use of using
    case Read: return "Read";
    case Write: return "Write";
    case Execute: return "Execute";
  }

  return "unknown";
}

int main()
{
  Permission permission{Permission::Read};

  const auto permissionStr{to_string(permission)};

  printf("%s\n", permissionStr.data());
}
#else
int main() {}
#endif