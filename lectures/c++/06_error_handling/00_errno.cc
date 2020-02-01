#include <cmath>
#include <iostream>

// errno is a preprocessor macro

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;

  // if an error is detected u should tell the user
  // if an error is fine we can reset it with
  // errno=0;
  
  d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;
  
  // who does change the value of errno? the function std::sqrt in this case
  return 0;
}
