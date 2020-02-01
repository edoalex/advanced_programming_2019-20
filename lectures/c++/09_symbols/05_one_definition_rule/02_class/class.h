#ifndef __class__
#define __class__

#include <iostream>

struct A {
  int a;
  A() { std::cout << "A ctor\n"; }
};

// A::A() { std::cout << "A ctor\n"; } // why not?
//not the same forfunctions! that's why I can't use this
#endif
