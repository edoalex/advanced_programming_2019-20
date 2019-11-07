#include <iostream>
#include <string>

template <typename num>
class Vector {
  num* elem;
  std::size_t _size;

 public:
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {}

  ~Vector() { delete[] elem; }
  
  auto size() const { return _size; }                              // auto now in c++14
  
  num& operator[](const std::size_t i) { return elem[i]; }         // why 2? const
  auto operator[](const std::size_t i) const { return elem[i]; }   // auto now in c++14
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

  std::cout << v << std::endl;
  return 0;
}
