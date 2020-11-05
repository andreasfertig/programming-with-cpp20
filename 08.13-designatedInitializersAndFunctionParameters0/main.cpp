// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

void FileAccess(bool open, bool close, bool readonly);

void Use()
{
  FileAccess(true, false, true);
}

void FileAccess(bool open, bool close, bool readonly) {}

void LLVM()
{
  FileAccess(/*open*/ true, /*close*/ false, /*readonly*/ true);
}

int main()
{
  Use();

  LLVM();
}