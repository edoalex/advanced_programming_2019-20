#include <iostream>

void get_int();
void get_double();

int main(){
  get_int();
  get_double();
}

void get_int(){
  int i;
  std::cout << "Insert a string with a valid integer: \n";
  while(!(std::cin >> i)){
       	std::cin.clear();
	std::cin.ignore();}
  std::cout << "Your integer is " << i << std::endl;
     }

void get_double(){
  double d;
  std::cout << "Insert a string with a valid double: \n";
  while(!(std::cin >> d)){
       	std::cin.clear();
	std::cin.ignore();}
  std::cout << "Your double is " << d << std::endl;
     }
