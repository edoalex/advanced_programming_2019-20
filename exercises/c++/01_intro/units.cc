#include <iostream>
#include <string.h>

int main(){
  int pos;
  std::string line;
  std::string s_numb;
  double numb;

  std::cout << "Insert a lenght in inches: \n";
  std::getline(std::cin, line);
  pos = line.find(" ");  /* operator "find" returns the position on the 
			    searched character */
  s_numb = line.substr(0, pos); /* operator "substring(a,b)" returns a string
				   from position a to b */
  numb = std::stod(s_numb); /* stod converts string to double */
  std::cout << 0.0254 * numb << " meters" << std::endl;
}
