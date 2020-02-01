#include <iostream>

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)    // here! (see later)
      : elem{new T[length]{}}, _size{length} {}

  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; } // const here means that it doesn't changes members of the class
  T& operator[](const std::size_t& i) { return elem[i]; } 
  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem; }            // returns pointer to first element
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }    // returns pointer to last element
  T* end() { return elem + size(); }
};

// added later
void print(const Vector<int>& v){
  for(auto x:v)
    std::cout << x << std::endl;
}
// end added later


int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  // I can use range-for-loop like the following now (useless in scope, but useful in showing)
  
  /* 
  auto it = v1.begin();
  auto stop = v1.end();
  for(;it!=stop; ++it)
      const auto x = *it;
  */

  std::cout << "v1: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // default copy constructor (copy by value!)
  
  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;
  
  // so v1 and v2 are entangled!! Not good
  // y is that? Cause the variables initialazed are the same (copy by value), but there's a pointer!
  // so the memory locations of v1 and v2 are the same!

  //print(7); // it work by implicit cast from int to const Vector<int> If and only if there's NO "explicit" in line 9!
  // implicit conversion to resolve the parameters to a function works only if ctor is callable with one single parameter
  // and of course there's no "explicit" in ctor definition
  return 0;
}
