#include <iostream>             // 3.7 s to read LittleWomen.txt with vectors
#include <string.h>
#include <vector>
#include <algorithm> // for std::find
#include <chrono>


void clean(std::string & s);             // cleans a word (removes .,:;!?" ecc. and converts to lowercase)




int main(){
  std::vector<std::string> v, uniq;
  std::string s;

  // store words in v

  std::cout << "Insert words. Press Ctrl-D when finished. \n";

  auto t0 = std::chrono::high_resolution_clock::now();
  
  while(std::cin >> s){
    clean(s);
    v.push_back(s);
  }
  
  // store only unique words in uniq and count the repetitions

  std::vector<int> rep;
  
  for(auto x:v){
    auto iter = std::find(uniq.begin(), uniq.end(), x);
    if(iter == uniq.end()){
      uniq.push_back(x);
      rep.push_back(1);
    }
    else{
      rep[ std::distance(uniq.begin() , iter) ] += 1;
    }
  }

  auto t1 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
  
  // print unique words and repetitions
  
  std::cout << std::endl;

  for(auto i=0u; i<uniq.size(); i++){
    std::cout << rep[i] << "\t" << uniq[i] << std::endl;
  }
  std::cout << "Total number of different words: " << uniq.size() << std::endl;
  std::cout << "Elapsed " << elapsed.count() << " [milliseconds]" << std::endl;

  return 0;}

void clean(std::string &s){
  static constexpr char c[]{'.', ',', ':', ';', '"', '?', '!', '(', ')',
      '[', ']', '{','}','<', '>', '*', '#', '%', '&', '+',
      '\t', '/', '\'', '-', '_', '='};

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
