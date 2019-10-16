#include <iostream>

int main(int argc, char* argv[]) {   //argc = argument counter. argv array that stores arguments given by command line in execution
  
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  return 0;
}
