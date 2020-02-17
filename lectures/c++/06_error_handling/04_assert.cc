#include <assert.h>
#include <cmath>
#include <iostream>

#include "ap_error.h"


// implement a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
    assert(d >= 0 && d <= 50);  // provided by C, no exceptions

  // assert(condition): if cond=T keep on; if cond=F program crushes (it calls the function abort() )
  // what's the pro? if compile with    flag -DNDEBUG  assertion won't be activated
  // in this way, compiling with or without -DNDEBUG, allows you to turn on or turn off the errors catch
  // to sum up: if there are checks in your code that slow down your program while developing, use assert to avoid them

  // AP_ASSERT(d>=0 && d<=50) <<  "d should be in the range [0,50]";

  // AP_ASSERT_IN_RANGE(d,0,50);
  return sqrt(d);
}
