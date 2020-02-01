#include "timer.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

timer<> t;

template <typename I>
void set_timed(const std::size_t n, I first, I last) {
  t.start();
  using value_type = typename std::iterator_traits<I>::value_type; //typename is necessary when the type is nested like this; 
  //without typename the compiler thinks that value_type is a static variable
  std::set<value_type> set{first, last};
  t.stop();
}

template <typename I>
void vector_timed(const std::size_t n, I first, I last) {
  t.start();
  using value_type = typename std::iterator_traits<I>::value_type;
  //std::vector<value_type> v{first, last};
  std::sort(first, last);
  auto it = std::unique(first, last); //this gets rid of the duplicates, but doesn't change the length of the vector, but returns the iterator to the first "empty" element
  //example: 1 3 2 1 3 5 ---> 1 1 2 3 3 5 ---> 1 2 3 5 * * * 
  //I also add [don't know] because otherwise the compiler doesn't execute the line with auto it = ... if it is never used
  t.stop();
  (void)std::distance(first,it);
}

using namespace std::chrono;
int main() {
  using value_type = int;
  for (std::size_t n = 16; n < (1 << 25); n <<= 1) { 
    // n<<=1 is a left bit shift: it's a multiplication for 2 but faster
    //n < (1 << 25) means n is less than 2^25
    std::vector<value_type> v(n);
    std::iota(v.begin(), v.end(), value_type(-1024)); // this guarantees no repetitions
    std::random_shuffle(v.begin(), v.end());
    for (std::size_t i = 0; i < n; ++i) {
      v[i] = int{v[i]} & 1023; //here i'm inserting repetitions with a mask (1023 has all the bits = to 1) (bit operation)
      //in this way all the numbers between 0 and 1023 will be the same; all the numbers above will be brought down to a number between 0 and 1023
      //ex: 1024 --> 0 ; 1025 --> 1 ecc.
    }
    std::cout << std::setw(15) << n << "\t";
    //set_timed(n,v.begin(),v.end()); //try to uncomment this and comment the following line to see what is better
    vector_timed(n, v.begin(), v.end()); // result: vector is faster!!
  }
}
