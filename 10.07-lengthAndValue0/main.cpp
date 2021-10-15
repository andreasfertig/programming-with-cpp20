// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>

bool write(const char*, size_t)
{
  return true;
}

bool Send(const char* data, size_t size);
void Read(char* data, size_t size);

void Use()
{
  char buffer[1'024]{};

  Read(buffer, sizeof(buffer));
  Send(buffer, sizeof(buffer));

  // some code in-between

  char buffer2[2'048]{};

  Read(buffer, sizeof(buffer2));
  Send(buffer, sizeof(buffer2));
}

bool Send(const char* data, size_t size)
{
  if(!data) { return false; }

  return write(data, size);
}

void Read(char* data, size_t size)
{
  if(!data) { return; }

  // fill buffer with data
}

int main()
{
  Use();
}