#include <iostream>

struct X {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors (I want the compiler to generate a default ctor)
};

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization  : a=5 b=uninit. c = in-class_init
  Y(const Y&) = delete;
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // only difference between result printing X or Y:
  // the assigned value to the double for X is:    random if X x1;    0 if X x2{}; because it calls default ctor (compiler gen.)
  // the assigned value to the double for Y is:    random both if    Y y1;   or   Y y2{};  because it calls custom ctor (written by me)
  
  // Y y3{y2}; // error: call to a deleted function

  return 0;
}
