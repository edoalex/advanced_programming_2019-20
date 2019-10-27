#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

// watch out when importing namespace! u could have conflicts (ex dec is ambigous)

// to use not the whole namespace but only something, I could use:
// using:: std::cout;
// using:: std::endl;

int main() {
  cout << nov << endl;
  // cout << dec << endl;

  return 0;
}
