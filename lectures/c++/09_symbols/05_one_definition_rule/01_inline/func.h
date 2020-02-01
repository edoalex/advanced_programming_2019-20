#ifndef _FUNC_H_
#define _FUNC_H_

#include <iostream>
//functions are external linkated by default; this is a problem if we only write void dummy() beause when we link the various libraries we have multiple definition of dummy()
//solutions: use static or inline (as here seen)
//differene: with inline you suggest the ompiler not to put a jump to that funtion, but to opy and paste the ontent of the funtion
//use it only with small funtionS! also, tthe ompiler can do what he wants: he an not inline inlined funtion or inline not inlined funtions;
//inline implies internal linkage in c++, in c it's not implied, you have to put static
inline void dummy() {
  std::cout << "dummy\n";
}

#endif /* _FUNC_H_ */
