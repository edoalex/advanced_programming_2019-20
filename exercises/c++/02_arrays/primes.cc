#include <iostream>

bool is_prime(unsigned int n){ 
  for(unsigned int divisor=2; divisor<n; divisor++){
    if(n%divisor == 0){
      return false;}}
  return true;}

int main(){
  unsigned int primes[50]; //since the array is not so long, I prefer to
  unsigned int cont=1;     //allocate it at first 'cause it's simpler
  unsigned int candidate=3;
  primes[0] = 2;
  
  while(candidate<100){
    if(is_prime(candidate)){
      primes[cont] = candidate;
      cont++;}
    candidate++;}

  for(int i=0; i<50; i++){
    if(primes[i] == 0){
      break;}
    std::cout << primes[i] << " ";}
  std::cout << std::endl;

  return 0;}
