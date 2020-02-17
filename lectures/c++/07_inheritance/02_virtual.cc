#include <ap_error.h>
#include <iostream>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(!(weight < 0)) << "invalid weight!\n";
  }

  Animal() : Animal{0, 0} {}  // delegating constructor
  // virtual allows children functions to ... (do what in the previous progr I couldn't do)
  virtual void speak() const = 0;  // pure virtual function ==> abstract class (if I've written =0)
  // when inherit I inherit data and interfaces: a function pure virtual can't be called (if I inerith virtual function, gotta use polymorphism)
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}  // why? see file 03_virtual_destructor.cc
  // Spoiler:
  // Using run-time polymorphism, to call the proper destructor (and not always and only the destructor of the base class),
  // the destructor of the base class must be virtual.
};

struct Dog : public Animal {                       // if I used virtual in the parent, I gotta use override in the child one
  void speak() const noexcept override { std::cout << "Bau\n"; }      // "overload": same func name, different args (not the case here)
                                                                      // override makes the compiler check if there's the virtual func in the parent
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  explicit Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; }
};

void print_animal(const Animal& a) noexcept {
  std::cout << "through ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};

    std::cout << "through pointer\n";
    p->info();
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}

// also an empty class occupies memory: sizeof(emp_class) returns 0
// but if I add a virtual to a func it's 8.. why?
// virtual table: when executing, the compiler executes until that call, a pointer takes it
// to the virtual table (funcs not enlined) that contains the copies of the function for all the derived classes
// if interested in hpc, u don't want to call a function that is called many times "virtual"
// u don't want jumps from the compiler in memory, cause it requires the creation of a pointer (to come back from memory)
