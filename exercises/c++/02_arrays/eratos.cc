#include <iostream>
#include <cmath>

int main(){
  std::cout << "Insert number: \n";
  unsigned int n;
  std::cin >> n;
  bool* primes{new bool [n]};
  
  for(unsigned int i = 0; i <= n; i++){
    primes[i] = true;}

  for(unsigned int i=2; i <= std::sqrt(n); i++){
    if(primes[i]){
      for(unsigned int j=i*i; j<=n; j = (j+i)){
	primes[j] = false;}
    }
  }
  std::cout << "Primes smaller than " << n << ": \n";
  for(unsigned int i=2; i<=n; i++){
    if(primes[i]){
      std::cout << i << std::endl;
    }
  }

  return 0;}
