#include <iostream>
#include <string>

int main(){
  int a[4]{1,2,3,4};
  const int* const end{a};

  std::cout << "a: " << a << std::endl;
  std::cout << "*a: " << *a << std::endl;
  std::cout << "end: " << end << std::endl;
  std::cout << "*end: " << *end << std::endl;
  std::cout << "*(end + 1): " << *(end + 1) << std::endl;
  


  return 0;}
