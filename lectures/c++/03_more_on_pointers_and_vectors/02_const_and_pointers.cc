#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};

  const int* pc{&a};             //const is -faster -helps u in compile time checking for errors. In this syntax i CAN'T modify the content of variable pointend by pc (that is a) from pc.
  
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a

  int* const cp{&a};           //in this case, instead, i CAN'T modify just the memory address to which cp points to
  a = b;
  *cp = 33;
  // cp = &b;   // error

  const int* const cpc{&a};    //in this case both: pointer to fixed memory location and i can't modify content of a from cpc.

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99;

  int aa[4]{};
  print_sentinel(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t l) {
  const T* const end{a + l};    //end{a+l} will point to the element afte the last element of the array
  
  for (; a != end; ++a)         // i can change a (pointer), i can't change value of a
    std::cout << *a << std::endl;
}
