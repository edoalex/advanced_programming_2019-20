#include <iostream>             // types are an implementation of a concept, I may have different types for the same concept

enum color { red, yellow, green };   // enum: box to avoid "magic numbers" (similiar to dict)
// enum color{red=0, yellow=1, green=2}; // equivalent

void dwim(const color c) {
  switch (c) {
    case red:
      std::cout << "option 1: red\n";
      break;
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly converts to integers

  dwim(opt);

  dwim(yellow);

  // dwim(2); // error
  dwim(color(2));  // works but why you may want to write this?

  dwim(color(6));  // it goes to default option

  return 0;
}
