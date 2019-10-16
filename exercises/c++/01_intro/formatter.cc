#include <iostream>
#include <string.h>

int main(){
  std::string line;
  std::string printable;
  int n_max = 25;
  int break_p;
  
  while(std::getline(std::cin, line)){
    while(line.length() > n_max){ /* if line is too long, search where to cut, 
				     else print it */
      unsigned int i{0};
	  while(!(line[n_max - i] == ' ')){
	    i++;}
	  break_p = n_max - i + 1;
	printable = line.substr(0, break_p);
	std::cout << printable << std::endl;
	line = line.substr(break_p);}
      std::cout << line << std::endl;
  }
  return 0;}
