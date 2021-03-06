#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope
  void f(char x) { std::cout << "char " << x << std::endl; }
};

int main() {
  bar b;
  b.f(33);      // it calls BAR function (if 8 line is commented)
                // it calls FOO function (if 8 line is UNcommented)
}
// the namespace of bar contains for sure bar::f(char) and, only if
// using foo:f is present, contains foo::f(int) too!
// message: overloading doesn't work with inheritance
// try to comment the 8 line and see difference
