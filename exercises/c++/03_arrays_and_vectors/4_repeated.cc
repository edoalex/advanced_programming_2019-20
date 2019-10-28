#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm> // for std::find


void clean(std::string & s);             // cleans a word (removes .,:;!?" ecc. and converts to lowercase)



int main(){
  std::vector<std::string> v, uniq;
  std::string s;

  // store words in v

  std::cout << "Insert words. Press Ctrl-D when finished. \n";

  while(std::cin >> s){
    clean(s);
    v.push_back(s);
  }
 
  // store only unique words in uniq
  
  for(auto x:v){
    if(std::find(uniq.begin(), uniq.end(), x) == uniq.end()){
      uniq.push_back(x);
    }
  }

  // print unique words
  
  std::cout << std::endl;

  for(auto x:uniq){
    std::cout << x  << std::endl;
  }

  return 0;}


void clean(std::string &s){
  static constexpr char c[]{'.', ',', ':', ';', '"', '?', '!', '(', ')',
      '[', ']', '{','}','<', '>', '*', '#', '%', '&', '+',
      '\t', '/', '\'', '-', '_','='};

  for(auto x:c){
    auto it = std::find(s.begin(), s.end(), x);
    while(it != s.end()){
      s.erase(it);
      it = std::find(s.begin(), s.end(), x);
    }
  }

  for(unsigned int i{0}; i<s.size(); i++){
    s[i] = std::tolower(s[i]);}
}
