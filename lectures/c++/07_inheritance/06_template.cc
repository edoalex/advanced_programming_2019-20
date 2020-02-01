#include <iostream>

// the base class is templated

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {
  void bar() const { this->foo(); }    // this is necessary, otherwise it doesn't compile
};

int main() {
  Derived<int> d;
  d.bar();
}

// if class is templated and compiling tells you u don't have access to st, use this
