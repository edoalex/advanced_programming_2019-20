#include <vector>

template <typename T>
void debug(T);

int main(){
  std::vector<int>v {1,2,3};
  auto it= v.begin();
  debug(it);

  return 0;}
