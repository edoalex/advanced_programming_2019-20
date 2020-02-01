#include "constants.h"
#include <iostream>

double area_circle(const double);
double golden_ratio(const double);
extern int circle_counter; //needed because I want to access the variable circle_counter
//if we omit "extern" the compiler will complain because there are two different variables with the same name
//in fact, there is only one copy of this variable

int main() {
  std::cout << area_circle(1) << std::endl;
  std::cout << area_circle(2) << std::endl;

  std::cout << golden_ratio(1) << std::endl;

  std::cout << circle_counter << std::endl;
  std::cout << "[main] pi = " << pi << std::endl;

  return 0;
}
