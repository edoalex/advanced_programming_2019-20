#ifndef _FUNC_H_
#define _FUNC_H_

#include <iostream>

template <class T = double>
void dummy() {
  T t{};
  std::cout << t << ": dummy\n";
}

//templates are fine from this point of view; do not compile templates, keep them in headers
//so function one definition rule is different!! if not templated you have to use static or --- otherwise you an do what you want.
#endif /* _FUNC_H_ */
