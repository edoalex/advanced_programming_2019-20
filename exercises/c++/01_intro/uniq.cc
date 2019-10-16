#include <iostream>

int main(){
  std::string line;
  std::string temp;
  int cont=1;

  std::getline(std::cin, temp);
  
  while(std::getline(std::cin, line)){
    if(line != temp){
      std::cout << cont << " " << temp << "\n";
      temp = line;
      cont = 1;}
    else{
      cont ++;} 
  }
  std::cout << cont << " " << temp << "\n";

}
