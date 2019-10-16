#include <iostream>
#include <vector>

bool is_prime(unsigned int n){
  for(unsigned int i=2; i<n; i++){
    if(n%i == 0){
      return false;}
  }
  return true;
}


int main(){
  std::vector<int> v;
  v.push_back(2);
  
  for(unsigned int candidate=3; candidate <= 100; candidate++){
    if(is_prime(candidate)){
      v.push_back(candidate);}
      }

   for(unsigned int index =0; index < v.size(); index++){
     std::cout << v[index] << std::endl;}

   return 0;}
