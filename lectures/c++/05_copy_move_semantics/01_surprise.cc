#include <iostream>

struct X {
  char member;
};

int main() {
  X x1;                 // default ctor (constuctor)
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor (since c++11)
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect?? an uninizialized character (x1 one) that is random, because char is a built-in type
  return 0;
}

// if u don't write nothing, the compiler calls a bunch of functions.. let's
// see em in the next codes (move, copy, default ctor)
