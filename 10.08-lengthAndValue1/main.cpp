// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <array>
#include <cstdio>

bool write(const char*, size_t)
{
  return true;
}

template<size_t SIZE>
bool Send(const std::array<char, SIZE>& data);

template<size_t SIZE>
void Read(std::array<char, SIZE>& data);

void Use()
{
  std::array<char, 1'024> buffer{};

  Read(buffer);
  Send(buffer);

  // some code in-between

  std::array<char, 2'048> buffer2{};

  Read(buffer2);
  Send(buffer2);
}

template<size_t SIZE>
bool Send(const std::array<char, SIZE>& data)
{
  return write(data.data(), data.size());
}

template<size_t SIZE>
void Read(std::array<char, SIZE>& data)
{
  // fill buffer with data
}

int main()
{
  Use();
}