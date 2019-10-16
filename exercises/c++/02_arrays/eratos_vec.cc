#include <iostream>
#include <vector>
#include <cmath>

int main(){
  unsigned int n;
  std::cout << "Insert a value: \n";
  std::cin >> n;
  std::vector<bool> primes(n, true);
  
  for(unsigned int i = 2; i <= std::sqrt(n); i++){
    if(primes[i]){
      for(unsigned j = i*i; j <= n; j = (j+i)){
	primes[j] = false;}
	}
      }
  std::cout << "Primes smaller than " << n << ": \n";
  
  for(unsigned int i = 2; i<= n; i++){
    if(primes[i]){
      std::cout << i << std::endl;}
  }
  

  return 0;}
