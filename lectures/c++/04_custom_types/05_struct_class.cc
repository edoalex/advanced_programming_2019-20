#include <array>
#include <iostream>
#include <vector>

// in c++ in a class u can put data AND functions
// in c++ in a structure u can put data AND functions
// the only difference is the default visibility of the symbols. In a class, the default is private, in struct is public.


struct Point_s {
  double x;
  double y;
  void print();
};  // note ; at the end

void Point_s::print() {
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}

class Point_c {
  double x;
  double y;

public:               // u can change the visibility of a (private to default) class with    public:
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;   // a function of a class can always access the data. The visibility is for other var
  }  // note no ; at the end                                            
};   // note ; at the end

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

  Point_s* p = &ps; // pointer to a class: when I wanna pass a class, it's better to pass the pointer (occupies less space)
  p->x = 0.0;       // arrow syntax
  p->print();

  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);     // push_back creates a COPY of the element in the vectore, it doesn't put the same elemente there
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
