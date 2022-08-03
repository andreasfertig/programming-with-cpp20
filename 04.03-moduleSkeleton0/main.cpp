// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if 0
module;  // #A Starts the module, only required, if we have legacy  includes
// Global module fragment, legacy #includes go here

[export] module AwesomeModule;  // #B Export if it is an interface
// Module Purview, imports go here

import x;         // #C Import something only visible in the module
export import y;  // #D Import something and export it

export
{
  // #E Export everything in here
}

export void Fun();  // #F Export individual symbol
void        Bun();  // #G This symbol stays in the module

#else

#endif
int main() {}
