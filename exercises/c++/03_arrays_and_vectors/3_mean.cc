#include <iostream>
#include <vector>
#include <string.h>  // std::stod     converts a string into a double type
#include <algorithm> // std::sort


int main(int argc, char* argv[]){
  std::vector<double> v;
  double d;
  std::string s;
  
  while(std::getline(std::cin, s)){
    d = std::stod(s);
    v.push_back(d);
  }
  
  std::sort(v.begin(), v.end());

  //compute mean

  double sum{};
  for(auto x : v){
    sum += x;}
  std::cout << "The mean value is: " << sum/v.size() << std::endl;

  //compute median
  
  double median;
  if(v.size()%2 == 0){
    median = ( v[v.size()/2] + v[(v.size()/2) - 1] ) / 2;
  }
  else{
    median = v[(v.size()-1) / 2];
  }
  std::cout << "The median value is: " << median << std::endl;

  return 0;}
