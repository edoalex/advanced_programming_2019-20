#include "ap_error.h"
#include <iostream>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(weight >= 0) << "invalid weight: " << weight << std::endl;
  }

  Animal() noexcept : Animal{0, 0} {}  // delegating constructor

  void speak() const noexcept { std::cout << "Unknown\n"; }
  void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }
};
// in the following way we say that a dog IS An animal
// we're saying ìn this way that dog access all the public (not private)  members of the parent
// in order to use private members I have to  pass through a public interface (but difficult) first
// PROTECTED members are like private ones. The only difference is that children can access them!
// if I use :private   : what was pub , pro or pri, becomes pri

struct Dog : public Animal {                                            // IS A       : public (inheritance)
  void speak() const noexcept { std::cout << "Bau\n"; }                 // HAS A      obj comp (like previous prog)
  Dog() noexcept = default;                                             // USE A      : protected, private
  Dog(const unsigned int a, const double d) : Animal{a, d} {}         // I'm using Animal ctor
};                                            // for Dog, speak() is redifined from parentn, while info is not
// for Snake, I redefine info() too

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  explicit Snake(const bool b) noexcept : Animal{}, dangerous{b} {}
  void info() const noexcept {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept { std::cout << "ssss\n"; }
};

// run-time (dynamic) polymorphism (u can pass a children to a function that accepts a parent)
// works only for reff and pntr, not values
void print_animal(const Animal& a) noexcept {
  std::cout << "through ref\n";
  a.info();
  a.speak();
}

// compile-time (static) polymorphism
template <class T>
void print_animal_template(const T& a) noexcept {
  std::cout << "through template\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Dog d;
    d.info();
    d.speak();

    std::cout << std::endl;

    Dog d1{0, 0.6};
    d1.info();
    d1.speak();

    std::cout << std::endl;

    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};
    std::cout << "through pointer\n";
    // a pointer to a base class can point to all the children!
    // BUT the pointer will work through the functios of the parent (info doesn't tell if it's dangerous)
    p->info();
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    std::cout << std::endl;

    print_animal_template(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
