#ifndef __find_if_hardcoded   // this is similiar to pragma once
#define __find_if_hardcoded

// we're coding LINEAR SEARCH

template <typename I, typename T>
  // requires I is Iterator
  // *I is of type T
I find_if_hardcoded(I first, I last, const T& value){
  // preconditions: [first, last)
  while( first != last && *first != value) ++first;
  return first;
}

// this code is hardcoded, that means that I should define another function if I just wanna a simple condition

#endif

// the easiest way to represent a list of abject is through pointers (sentinel approach)
// iterators are a generalization of pointers
// it makes sense to return an iterator when I search something
// precondition impossible to compute: if it was an array I could minorate the adresses, but it may also be a linked list, where pointers are not ordined


// let's generalize the algorithm: what if we don't want just an equality?
template <typename I, typename P>
  // requires I is Iterator
  // *I is of type T
  // P has operator(T) and returns a bool
I find_if_template(I first, I last, P predicate){
  // preconditions: [first, last)
  while( first != last && !predicate(*first) ) ++first;
  return first;
}

// that function is an unary predicate given during the call
// I could also have been more specific:
//    I find_if_hardcoded(I first, I last, bool (*predicate)(const T&))
// Here, I sould pass a funtion, a lambda func., a class's funct...
//  P can be whatever, but must be known at compile time


// Let's use some OOP now:

// define predicate_base (see down) . it's an abstract class
template <typename T>
struct predicate_base{
  virtual bool operator()(const T&) const = 0;     // pure abstract ovreloading of () operator. The user will overload it for the children
};                                                 // and at run-time the right function will be invoked

template <typename I, typename T>
  // requires I is Iterator
  // *I is compatible with predicate
I find_if_virtual(I first, I last, const predicate_base<T>& predicate){
  // preconditions: [first, last)
  while( first != last && !predicate(*first) ) ++first;
  return first;
}

// dynamic polym. works only with references and pointers, not values
// we gotta define predicate_base now (UP! the func)
// it will be the parent class of everything that can be passed to the function as the "predicate" variable

// Between the last 2 functions, what are the performances?
