// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

int main()
{
#ifdef NDEBUG
#  define assert(condition) ((void)0)
#else
#  define assert(condition) /*implementation defined*/
#endif
}