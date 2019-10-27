#include <iostream>
#include <string>

// many constructors, but only one destructor when the variable goes out-of-scope
// scope: space between 2 curly braces
// for some type (ex vector) destructor is autom. called when the variable goes out-of-scope
// new calls the constructor, malloc won't
// delete calls the distructor, free won't

// functions defined inside the structure are enlined (in the binary there's no jump to
// the location of the function, but a copy of that, when u call it)

struct Foo {
  int _i;
  double _d;
  std::string _s;

  Foo(const int i, const double d,
      const std::string& s);  // custom constructor

  Foo();  // default constructor (needed if u wanna have an array of this object)

  ~Foo();  // destructor
};

Foo::Foo(const int i, const double d, const std::string& s)   // first region "limbo" (before { ) in which variables are not constructed yet
    : _i{i},                                                  //  in { }, variables are already constructed
      _d{d},
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared

{
  // _i{i};     would be an error, _i has been already constructed
  // _i = i;    would be fine (but I already did it in the constructor in a faster way)
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {
  std::cout << "dtor\n";
}

std::ostream& operator<<(std::ostream& os, const Foo& f) {     // operatorx change the operator x whatever it is (op overloading)
  os << f._i << " " << f._d << " " << f._s << std::endl;       // std::ostream can be assign to a std::cout (os in this case)
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error

  Foo f2{8, 2.2, "hello"};
  // Foo f2(8, 2.2, "hello");   // valid too
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope
  // never invoke a destructor by hand
  // the destructor destroys variables from the last inizialized to the first one
  return 0;
}
