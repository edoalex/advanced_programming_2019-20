#include <iostream>
//the size of this class is the size of int; all the other object are static so they live outside of the class
struct Foo {
  static double s;  // must be defined outside the class
  // static int si = 0; // error: must be const
  static const int sc = 9;  // only integral types are allowed
  // static const double sd;  // error
  int i;
};

double Foo::s;//this is necessary, otherwise s is not defined

// double Foo::s = 0;
// double Foo::s = 9;

// int Foo::i = 2; // error, only static members can be defined out of class

int main() {
  Foo::s = 77.88;
  Foo f1;
  Foo f2;
    //of course they share the value of the static variables! so in this ase f1.s == f2.s == Foo:s
  std::cout << sizeof(f1) << std::endl;
  std::cout << f1.s << '\n' << f2.s << '\n' << Foo::s << std::endl;
  return 0;
}
