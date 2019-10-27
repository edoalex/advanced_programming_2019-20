#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc;
  
  int* ap[7];            //array where each element is a pointer to integer
  

  void* pv{pi};          //pointer to void inizialazed from pointer to something (int)       
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment. Why? Beacuse u don't know the type, so the size of every element and the jumps to do
  int* pi2{static_cast<int*>(pv)};  //from void point to int point. static_cast performed at compile time

  pv = ppc;
  pv = ap;
  pv = pi;

  pi = nullptr;         //points to nothing
  ppc = nullptr;
  // ap = nullptr;  // error, why? cause it's an array of pointers, not a pointer
  ap[0] = nullptr;
  int** bbb;
  bbb = ap;
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr

  // pi = NULL; // please don't do this

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer
  da = nullptr;

  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi)                // pi = (pi != nullpointer) cause it returns 0 (false)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)   
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  // strings are special type of char[]
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

  int (*fp)(const char*);        //defines a pointer to function that take const char* as input e return an int. Parenthesis are mandatory
  fp = func1;

  fp("hello");

  fp = &func2;                   //same operation of last comment, but different syntax
  fp("world");

  // fp = func3; // error: wrong signature
  auto xx = func3;

  xx("auto");

  decltype(&func3) x = func3;    //similiar to auto. Define variable x of type (&func3) pointer to function. Like {void (*x) (const char *) = func3}
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
