#include <iostream>
#include <string>

template <typename num>
class Vector {
  num* elem;
  std::size_t _size;

 public:
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {}
  ~Vector() { delete[] elem; }
  
  auto size() const { return _size; }                              
  num& operator[](const std::size_t i) { return elem[i]; } 
  auto operator[](const std::size_t i) const { return elem[i]; }
  const num* begin() const{ return elem;}
  const num* end() const{return (elem + _size);}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  for (auto i = v.begin(); i<v.end(); ++i)  // is it what was meant to be implemented??
    std::cout << *i << std::endl;

  return 0;
}
