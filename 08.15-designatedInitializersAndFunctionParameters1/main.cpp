// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

struct FileAccessParameters {
  bool open;
  bool close;
  bool readonly;
};

void FileAccess(const FileAccessParameters& params);

void FileAccess(const FileAccessParameters& params) {}

int main()
{
  FileAccess({.open = true, .close = false, .readonly = true});
}