// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

class SomeClass {
  int c;

public:
  void SomeCleverMethod()
  {
    // #A Lambda internals created by the compiler
    class __lambda_8_18 {
    public:
      int operator()() const { return __this->c * 2; }

    private:
      // #B The captured object, a pointer to SomeClass
      SomeClass* __this;

    public:
      __lambda_8_18(SomeClass* _this)
      : __this{_this}
      {}
    };

    __lambda_8_18 twice = __lambda_8_18{this};  // #C Passing this
    const int v         = twice.operator()();
  }
};

int main() {}