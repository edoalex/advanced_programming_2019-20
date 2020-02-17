#ifndef _FUNC_H_
#define _FUNC_H_

#include <iostream>

template <class T = double>
void dummy() {
  T t{};
  std::cout << t << ": dummy\n";
}

// Templates are fine from this point of view;
// do not compile templates, keep them in headers.
// So function one definition rule is different!!
// If not templated you have to use static or inline,
// otherwise you can do what you want.
#endif /* _FUNC_H_ */
