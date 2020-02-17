#include <iostream>
#include <memory>  // std::unique_ptr

// smart pointers (std::unique_ptr):  implementation of the concept of "ownership"

template <typename T>
class Vector {
  std::unique_ptr<T[]> elem;
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem.get(); }
  T* begin() { return elem.get(); }

  const T* end() const { return elem.get() + _size; }
  T* end() { return elem.get() + _size; }
};

int main() {
  Vector<double> v1{7};
  // Vector<double> v2{v1}; // error compiling: default copy ctor calls 
  // a deleted function by std::unique_ptr
  // ... so, unique_ptr prevents from entangled vectors but doesn't solve the
  // problem just like this.. z see next program
  return 0;
}
