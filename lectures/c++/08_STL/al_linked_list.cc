#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include <vector>

#include "ap_error.h"

enum class method { push_back, push_front };

template <class T>
class List {
  struct node {
  	//here we have access to all the data of the nesting class List
  	//why do we implement a nested struct? 
    //because the user doesn't need to know the details, for example the implementation of a node
    //so we put this in the private part of the class List
    std::unique_ptr<node> next;
    T value;
    //In the following lines it makes no difference to put before "value" or "next"; the values do not depend on each other. 
    //But the compiler gives a warning if we swap them, because it could cause an error
    //in general it's better to do it in the correct order
    node(const T& v, node* p) : next{p}, value{v} {
      std::cout << "copy ctor" << std::endl;
    }
    node(T&& v, node* p) : next{p}, value{std::move(v)} {
      std::cout << "move ctor" << std::endl;
    }
    //this constructor is used in the list copy constructor [in theory]
    //this constructor takes as input a (unique) pointer to a node
    //initiate a new node with:
    //value = the value of the given node
    //next = the pointer of the given node, using make_unique since we are using unique pointers, if there is a pointer (not nullptr)
    //it is an iterative function if called on an existing node of a list (if it is not the last one)!!
    explicit node(const std::unique_ptr<node>& p) : value{p->value} {
      if (p->next){
        next = std::make_unique<node>(p->next);
      }
    }
  };

  std::unique_ptr<node> head;

  //probably implemented after
  template <class OT>
  void push_back(OT&& v);

  template <class OT>
  void push_front(OT&& v) {
    //all this could be done in one line
	/*
	auto h = head.release();
	auto new_node = new node{v,h};
	head.reset(new_node);
	*/

    // head.reset(new node{v, head.release()}); // this is pre c++14

    head = std::make_unique<node>(std::forward<OT>(v), head.release()); //this since c++14
  }
  // void push_front(T&& v);

  //implemented after
  node* tail() noexcept;

 public:
 	//[with or without the l is the same here]
  List() noexcept = default; // default constructor
  List(List&& l) noexcept = default; // one feature of the move semantic is that they don't throw exceptions
  List& operator=(List&& l) noexcept = default;
  
  //it would be a mistake to put noexcept here in the following, which uses the copy semantic;
  //in general, noexcept is put in move semantic, not in copy semantic
  List(const List& l);
  List& operator=(const List& l);

  template <class OT>
  void insert(OT&& v, const method m);


  //friend std::ostream& operator<<(std::ostream&, const List&); would be the same?
  //our function is templated so this is not good, so we do the following
  template <class O>
  friend std::ostream& operator<<(std::ostream&, const List<O>&);
  //this friend is needed because the operator<< needs to access to the private value of the nested class Node
  //this function has a template down there so we need a template here too
  //and you can't use the T because it would get in conflict with before used template
  //that's why we use the O instead of the T here


  template <typename O>
  class __iterator;//class iterator implemented after

  using iterator = __iterator<T>; //an alias
  using const_iterator = __iterator<const T>;



  iterator begin() noexcept {return iterator{head.get()}; }
  iterator end() {return iterator{nullptr};}

  //THESE TWO ARE EQUAL; WHY???
  
  const_iterator begin() const {return const_iterator{head.get()};}
  const_iterator end() const {return const_iterator{nullptr};}
  
  const_iterator cbegin() const {return const_iterator{head.get()};}
  const_iterator cend() const {return const_iterator{nullptr};}

};

template <typename T>
template <typename O>
class List<T>::__iterator{
  using node = typename List<T>::node;
  node * current;

public:
  explicit __iterator(node * x) noexcept : current{x} {} //better to use explicit to avoid unwanted automatic cast
  using value_type = O; //iterator is templated on this
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type&;
  using pointer = value_type*;
  //I'm only interested in the value here!!
  reference operator*() const noexcept {return current -> value;}
  pointer operator->() const noexcept {return &(*(*this));}

  __iterator& operator++() noexcept{ //only the pre increment
    current = current->next.get();
    return *this;
  }
  //if you want to implement the post increment this is the way
  __iterator operator++(int) noexcept{
    __iterator tmp{current};
    ++(*this);
    return tmp;
  }
  //these following "friend" are needed to access the private values of the class List
  friend bool operator==(const __iterator& a, const __iterator& b) {
    return a.current == b.current;
  }
  friend bool operator!=(const __iterator& a, const __iterator& b) {
    return !(a == b);
  }

};

template <class T>
typename List<T>::node* List<T>::tail() noexcept {
	//notice that this function will cause segmentation fault if we call it with an empty head
	//but there is no problem because we call this function only after controlling if there is already a head or not
  auto tmp = head.get();

  while (tmp->next)
    tmp = tmp->next.get();

  return tmp;
}

template <class T>
template <class OT>
void List<T>::insert(OT&& v, const method m) { // here you are going to call the move semantic (&&)
  if (!head) {// equivalent of if(head == nullptr); this will be called only if the list is empty
    // head.reset(new node{v,nullptr});
    head = std::make_unique<node>(std::forward<OT>(v), nullptr);
    //the difference here is that the = will be the move assignment; 
    //it will call a new and pass this values: this will be shown in the next lesson
    return;
  }
  //if the list is not empty:
  switch (m) {
    case method::push_back:
      push_back(std::forward<OT>(v));
      break;
    case method::push_front:
      push_front(std::forward<OT>(v));
      break;
    default:
      AP_ERROR(false) << "Unknown insertion method";
      break;
  };
}

template <class T>
template <class OT>
void List<T>::push_back(OT&& v) {
  node* last = tail(); //initialize a pointer to a node that point to the last node
  // last->next.reset(new node{v, nullptr});
  last->next = std::make_unique<node>(std::forward<OT>(v), nullptr);
  //the value of the pointer "next" of the last node becomes a pointer to another node, created now with value v and next nullptr 
  
  //if we wrote in c++14 style the following instead:
  //last->next = std::make_unique<node>(v, nullptr);
  //it wouldn't compile. Why? We will see it when we compile. 
  //Thanks to the dick (Edo questa è per te)
}

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
	//I enter this while loop only if I have at least one node, otherwise the following returns nullptr
  auto tmp = l.head.get();
  while (tmp) {//equal to while(tmp!=nullptr)
    os << tmp->value << " ";
    tmp = tmp->next.get();
  }
  return os;
}

template <class T>
List<T>::List(const List& l) {
  // auto tmp = l.head.get();
  // while(tmp){
  //   insert(tmp->value,method::push_back);
  //   tmp=tmp->next.get();
  // }
  //or, using the explicit constructor defined in the class:
  head = std::make_unique<node>(l.head);
}

int main() {
  try {
    List<int> l{};

    l.insert(4, method::push_back);
    l.insert(5, method::push_back);
    l.insert(3, method::push_front);

    std::cout << l << std::endl;

    std::vector<int> v(3);

    //std::copy(l.begin(), l.end(), v.begin()); //not written by sartori
    std::copy(l.cbegin(), l.cend(), v.begin());
    for (auto x : v)
      std::cout << x << std::endl;
    //auto ol = l;
    int a = 9;
    l.insert(14, method::push_front);//this will call the move ctor because 14 is an rvalue (thanks to std::forward)
    l.insert(a, method::push_front);//this will call the copy ctor because a is an lvalue (thanks to std::forward)

    std::cout << l << std::endl;
    //std::cout << ol << std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
