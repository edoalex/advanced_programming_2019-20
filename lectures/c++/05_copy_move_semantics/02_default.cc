#include <iostream>
#include <string>

struct S {
  int a;
  double b;
  std::string s; // default ctor of string set s to empty string
};

int main() {
  S s1;  // calls default constructor

  S s2{1, 2.3, "alberto"};  // if there are no custom ctors I can      custom ctor = ctor that I know (I wrote) 
                            // directly initialize the members. Note
                            // that I need access (i.e. they must be
                            // public)
  // it is called aggregate initialization (see
  // https://en.cppreference.com/w/cpp/language/aggregate_initialization)

  S s3{};  // calls {} on each member: S s3 { {}, {}, {} };

  std::cout << s1.a << "--" << s1.b << "--" << s1.s << "\n";
  std::cout << s2.a << "--" << s2.b << "--" << s2.s << "\n";
  std::cout << s3.a << "--" << s3.b << "--" << s3.s << "\n";

  return 0;
}

// with S s1;   values are randomly inizialized
// with S s1{}; values are inizialized to a default behaviour
// in every case, if the type is not built-in, but custom type, it has a default value of initialization
// even with   S s1;
// default value of int and double: 0
// default value of std::string: ""
