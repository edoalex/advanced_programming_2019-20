#include <iostream>             // 0.4 s to read LittleWomen.txt with map
#include <string.h>
#include <vector>
#include <algorithm> // for std::find
#include <chrono>
#include <map>


void clean(std::string & s);             // cleans a word (removes .,:;!?" ecc. and converts to lowercase)

int main(){
  std::map<std::string, unsigned int> m;
  std::string s;

  // store words (as keys) and number of repetitions (as value) in m

  std::cout << "Insert words. Press Ctrl-D when finished. \n";

  auto t0 = std::chrono::high_resolution_clock::now();
  
  while(std::cin >> s){
    clean(s);
    ++m[s];
  }
  
  auto t1 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
  
  // print unique words and repetitions
  
  std::cout << std::endl;

  for (const auto& p : m){
    std::cout << p.second << "\t" <<p.first << std::endl;
  }

  std::cout << "Total number of different words: " <<  m.size() << std::endl;
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
