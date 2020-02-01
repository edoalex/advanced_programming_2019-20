#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include "ap_error.h"

enum class method { push_back, push_front };

template <class T>
class List {
  struct node {
  	//here we can read all the data of the nesting class
  	//why a nested struct? the user doesn't need to know the details: 
  	//for example the implementation of a node so we put this in the 
  	//private part of the List
    std::unique_ptr<node> next;
    T value;
    //In the followings it makes no different to put before value or next; 
    //the values do not depends on each other. 
    //But the compiler gives a warning if we swap them, because it could cause an error, 
    //so better to do it in the correct order
    node(const T& v, node* p) : next{p}, value{v} {
      std::cout << "copy ctor node" << std::endl;
    }
    node(T&& v, node* p) : next{p}, value{std::move(v)} {
      std::cout << "move ctor node" << std::endl;
    }
    explicit node(const std::unique_ptr<node>& p) : value{p->value} {
      if (p->next)
        next = std::make_unique<node>(p->next);
    }
  };

  std::unique_ptr<node> head;

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

  node* tail() noexcept;

 public:
 	//with or without the l is the same here
  List() noexcept = default; // default constructor
  List(List&& l) noexcept = default; // one feature of the move semantic is that they don't throw exceptions
  List& operator=(List&& l) noexcept = default;
  
  //it would be a mistake to put noexcept here in the following, which uses the copy semantic: 
  //in general, noexcept is put in move semantic, not in copy semantic
  List(const List& l);
  List& operator=(const List& l);

  template <class OT>
  void insert(OT&& v, const method m);


  	//friend std::ostream& operator<<(std::ostream&, const List&); would it be the same?
  	//our function is templated so this is not good,
	//so we do the following
  template <class O>
 friend std::ostream& operator<<(std::ostream&, const List<O>&);

  //this function has a template down there so we need a template here too
  //and you can't use the T because it would get in conflict with before used template
  //that's why we use the O instead of the T here

  // Moreover, the friend keyword allows the operator << to access to private member of the class passed, such as the head!
  
  // from NOW the new stuff

  template <typename O>
  class __iterator;


  using iterator = __iterator<T>;
  using const_iterator = __iterator<const T>;
  
  iterator begin() noexcept { return iterator{head.get()}; }
  iterator end() { return iterator{nullptr}; }
  
  const_iterator begin() const { return const_iterator{head.get()}; }
  const_iterator end() const { return const_iterator{nullptr}; }
  
  const_iterator cbegin() const { return const_iterator{head.get()}; }
  const_iterator cend() const { return const_iterator{nullptr}; }
};

template <typename T>
template <typename O>
class List<T>::__iterator{
  using node = typename List<T>::node;
  node * current;
public:
 explicit __iterator(node * x) noexcept: current{x} {}

  using value_type = O;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type&;
  using pointer = value_type*;

  reference operator*() const noexcept { return current->value; }
  pointer operator->() const noexcept { return &(*(*this)); }

  __iterator& operator++() noexcept {
    current = current->next.get();
    return *this;
  }

  __iterator operator++(int) noexcept {
    __iterator tmp {current};
    ++(*this);                                   // use PREincrement, it's faster!
    return tmp;
  }

  friend
  bool operator==(const __iterator& a, const __iterator& b){
    return a.current == b.current;
  }

  bool operator!=(const __iterator& a, const __iterator& b){
    return a.current != b.current;
  }  
};

template <class T>
typename List<T>::node* List<T>::tail() noexcept {
	//notice that this function will cause segmentation fault if we call it with an empty head
	//but there is no problem because we call this function only after controlling 
	//if there is already a head or not
  auto tmp = head.get();

  while (tmp->next)
    tmp = tmp->next.get();

  return tmp;
}

template <class T>
template <class OT>
void List<T>::insert(OT&& v, const method m) { // here you are going to call the move semantic (&&)
  if (!head) {// equivalent of if(head == nullptr)
    // head.reset(new node{v,nullptr});
    head = std::make_unique<node>(std::forward<OT>(v), nullptr);
    //the difference here is that the = will be the move assignment; 
    //it will call a new and pass this values: this will be shown in the next lesson
    return;
  }
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
  node* last = tail();
  // last->next.reset(new node{v, nullptr});
  last->next = std::make_unique<node>(std::forward<OT>(v), nullptr);
  // if we wrote in c++14 style the following instead:
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
	//or
  std::cout << "copy ctor list" << std::endl;
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

    std::copy(l.begin(), l.end(), v.begin());

    for(auto x:v)
      std::cout << x << std::endl;
    

    auto ol = l;
    int a = 9;
    l.insert(14, method::push_front);
    l.insert(a, method::push_front);

    std::cout << l << std::endl;
    std::cout << ol << std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
