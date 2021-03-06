#include <iostream>

template <typename T>
T* alloc(std::size_t n){
  T* da = new T [n];
  std::cout << "Insert array values:" << std::endl;
  for (std::size_t i = 0; i<n; i++){   //try with std::size_t
    std::cin >> da[i];}
  return da;}

template <typename S>
void print_rev(std::size_t n, S* da){
  for(std::size_t i=n; i!= 0; i--){
    std::cout << da[i-1] << " ";}
  std::cout << std::endl;}


int main(){
  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
  
  int* pippo = alloc<int>(n);
  print_rev(n, pippo);
  delete[] pippo;

  double* pippa = alloc<double>(n);
  print_rev(n, pippa);
  delete[] pippa;
  
  return 0;}
