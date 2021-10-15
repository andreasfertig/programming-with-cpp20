// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstdio>
#include <span>

bool write(const char*, size_t)
{
  return true;
}

bool Send(const std::span<char>& data);
void Read(std::span<char> data);

void Use()
{
  std::array<char, 1'024> buffer{};

  Read(buffer);
  Send(buffer);

  // some code in-between

  char buffer2[2'048]{};

  Read(buffer2);
  Send(buffer2);
}

bool Send(const std::span<char>& data)
{
  return write(data.data(), data.size());
}

void Read(std::span<char> data)
{
  // fill buffer with data
}

int main()
{
  Use();
}