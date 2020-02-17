#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  // ~Base() { std::cout << "~Base\n"; }
  virtual ~Base() { std::cout << "~Base\n"; }
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }   // i'm creating AND deleting d
  std::cout << "\n\npointers\n";
  Base* p = new Derived;
  delete p;  // deleting p ONLY calls Base dtor! To avoid it, insert virtual to functions u want to be inheritated
  return 0;
}
// u construct from base to children and destroy viceversa
