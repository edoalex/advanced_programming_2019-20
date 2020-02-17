#include <algorithm>  // std::copy
#include <iostream>
#include <memory>    // std::unique_ptr

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized                 \\ what will be the size?  random int 
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could      \\ and here insted?        0
  // be better Vector() = default;

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // end of copy semantics
  /////////////////////////

  /////////////////////////   // move is like stealing
  // move semantics          // when i say a=b i'm coping (creating another object), move is better for swapping.

  /*   best swap strategy
  auto x = std::move(a);
  a = std::move(b);
  b = std::move(x);
  */

  // rvalue: can only be on the right of = (ex a=3; 3 is rvalue)

  
  // move ctor    // in calling, i can distinguish this from copy ctor for rvalue
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {  // && v     means that v is an rvalue
                                                                             // v is gonna die at the end of the line
    std::cout << "move ctor\n";
  }

  // Vector(Vector&& v) = default; // ok (cause we have unique_ptr, not raw pointers)

  // move assignment
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    return *this;      // cause I can chain a=b=c.... 'this' is like 'self' in python.. 'this' is a pointer to myself
  }

  // Vector& operator=(Vector&& v) = default; // ok

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor       // in this way, unique_ptr s are different(in value), but size and value of the elements are the same
template <typename T>
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin());
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //

  elem.reset();              // first of all clean my memory
  auto tmp = v;              // then use copy ctor
  (*this) = std::move(tmp);  // finally move assignment

  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx? No! I would just delete vx and invoke an error
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {  // implement sum of vectors
  const auto size = lhs.size();

  // how we should check that the two vectors have the same size?

  Vector<T> res(size);    // calls custom ctor
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};

  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used (z empty), otherwise it calls segmentation fault
  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  //v3=v3;     // disaster if uncomment. reason: line 113
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};    // why does it call custom ctor and not copy ctor? cause custom ctor is called
                                 // by sum operation. But anyway why not copy ctor afterwards? cause sum returns vector already?
  // st added later
  std::cout << "\nVector<double> v5{v4}; calls\n";
  Vector<double> v5{v4};
  // end added later
  
  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;       // why after 3 custom ctor (for sums) calls move assgn and not copy assgn? For NRVO:
  std::cout << "v4 = " << v4;   // since + returns a vector, instead of copying it into v4, I just create that last vector
                                // returned by + already into v4 memory space! If compiler doesn't undestand this, at least it
                                // moves the value returned into v4, it doesn't copy it
  return 0;
}
