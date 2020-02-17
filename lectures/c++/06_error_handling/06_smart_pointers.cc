#include <iostream>
#include <memory>  // std::uniqe_ptr

#include "ap_error.h"

// shared pointers are slower than raw pointers, but allow many people to access it
// unique pointers are as fast as raw pointers, use them when u know who gotta deal with it at the death
// message: use smart pointers

class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector ctor\n";
  }
  double& operator[](const unsigned int i) noexcept {     // put 'noexcept' in a function if u'r sure that it doesn't raise error (not the functions called inside)
    return elem[i];                                       // it will increase the performance. If errors are raised, the program crushes. Abort.
  }                                                       // you can use smart pointers almost like raw pointers
  ~Vector() noexcept { std::cout << "~Vector\n"; }
};

class ManyResources {
  std::unique_ptr<double[]> ptr;
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
    std::unique_ptr<int[]> up{new int[7]};
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}

// from now on:    int main(){   try and catch boxes     return 0;}
