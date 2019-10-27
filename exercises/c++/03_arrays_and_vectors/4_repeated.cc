#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm> // for std::find


bool breakable(std::string s);           // checks if string s contains spaces
unsigned int find_brk(std::string s);    // returns the break point in which string s should be cut
void clean(std::string & s);             // cleans a word (removes .,:;!?" ecc. and converts to lowercase)



int main(){
  std::vector<std::string> v, uniq;
  std::string s, almost_pushable;

  // store words in v

  std::cout << "Insert words. Press Ctrl-D when finished. \n";
  
  while(std::getline(std::cin, s)){
    while(breakable(s)){        // the different words in the string will be removed step by step from the end
      unsigned int brk_pnt{ find_brk(s) };
      if(brk_pnt == s.size() - 1){
	s.erase(brk_pnt, 1);
      }
      else{
      almost_pushable =  s.substr( brk_pnt + 1 );
      clean(almost_pushable);
      v.push_back( almost_pushable );
      s = s.substr(0, brk_pnt);
      }
    }
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
    std::cout << x << "." << std::endl;
  }

  return 0;}


bool breakable(std::string s){
  if(std::find(s.begin(), s.end(), ' ') == s.end()){
    return false;
  }
  else{
    return true;
  }
}


unsigned int find_brk(std::string s){
  unsigned int i{0};
 while(s[s.size() - i]  != ' '){
	i++;
      }
 unsigned int brk_pnt = s.size() - i;
 return brk_pnt;
}

void clean(std::string &s){
  char c[24]{'.', ',', ':', ';', '"', '?', '!', '(', ')',
      '[', ']', '{','}','<', '>', '*', '#', '%', '&', '+',
      '\t', '/', '\''};
  for(auto x:c){
    while( std::find(s.begin(), s.end(), x) != s.end() ){
      unsigned int i{0};
      while( s[s.size() - i] != x){
	i++;}
      unsigned int rmv{static_cast<unsigned int>(s.size()) -i};
      s.erase(rmv, 1);
    }
  }
  for(unsigned int i{0}; i<s.size(); i++){
    s[i] = std::tolower(s[i]);}
}
