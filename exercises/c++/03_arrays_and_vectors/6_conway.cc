/*
Game of life is implemented with 'Gosper glider gun' initial condition, that requires NON-periodic boundary conditions. 
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <unordered_map>
#include <vector>
#include <iomanip>

template <typename T>   // print the grid
void show(T m, unsigned int r, unsigned int c);

template <typename T>  // construct Gosper gun initial condition
void init(T &m, unsigned int r, unsigned int c);

template <typename T>  // refresh grid
T update(T m, unsigned int r, unsigned int c);

template <typename T>  // check how many alive cells are in the neighborhood of (i,j)
unsigned int check_neig(T m, unsigned int r, unsigned int c,  unsigned int i, unsigned int j);


int main(){
  const int r{30};
  const int c{40};
  std::array<char, r*c> grid;

  init(grid, r, c);
  show(grid, r, c);

  while(1){
    grid = update(grid, r, c);
    show(grid, r, c);
    std::this_thread::sleep_for (std::chrono::milliseconds(50));
  }
  return 0;
}



template <typename T>  // construct Gosper gun initial condition
void init(T &m, unsigned int r, unsigned int c){
  unsigned int i, j;
  for(i=0; i<r; i++){        // at first write . everywhere... (dead points)
    for(j=0; j<c; j++){
      m[i*c + j] = '.';
    }
  }

  std::unordered_map<int, std::vector<int>> ins;   // and then write # only where needed (alive points)
  // insert ( j , set_of_i_for_that_j   )
  ins.insert( std::pair<int, std::vector<int>>(2, {10,11}) );
  ins.insert( std::pair<int, std::vector<int>>(3, {10,11}) );
  ins.insert( std::pair<int, std::vector<int>>(14, {9,10,11,12,13}) );  
  ins.insert( std::pair<int, std::vector<int>>(15, {8,10,11,12,14}) );
  ins.insert( std::pair<int, std::vector<int>>(16, {9,13}) );
  ins.insert( std::pair<int, std::vector<int>>(17, {10,11,12}) );
  ins.insert( std::pair<int, std::vector<int>>(18, {11}) );
  ins.insert( std::pair<int, std::vector<int>>(22, {9}) );
  ins.insert( std::pair<int, std::vector<int>>(23, {9}) );
  ins.insert( std::pair<int, std::vector<int>>(24, {8,10}) );
  ins.insert( std::pair<int, std::vector<int>>(25, {7,8,10,11}) );
  ins.insert( std::pair<int, std::vector<int>>(26, {6,12}) );
  ins.insert( std::pair<int, std::vector<int>>(27, {9}) );
  ins.insert( std::pair<int, std::vector<int>>(28, {6,7,11,12}) );
  ins.insert( std::pair<int, std::vector<int>>(31, {10}) );
  ins.insert( std::pair<int, std::vector<int>>(32, {10}) );
  ins.insert( std::pair<int, std::vector<int>>(33, {11}) );
  ins.insert( std::pair<int, std::vector<int>>(36, {8,9}) );
  ins.insert( std::pair<int, std::vector<int>>(37, {8,9}) );

  for(auto el=ins.begin(); el != ins.end(); el++){
    j = el->first;
    for (auto i:ins[j]){
      m[i*c + j] = '#';
    }
  }
}

template <typename T>
T update(T m, unsigned int r, unsigned int c){
  auto carbon = m;                // a copy of the original grid is needed to write generational changes there. Otherwise
  unsigned int alive_neig, i, j;  // generation n+1 may influence generation n.
  
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      alive_neig = check_neig(m, r, c, i, j);
      if( m[i*c + j] == '.' ){                      // if u'r dead
	if( alive_neig == 3 ){                      // and if u'r blessed
	  carbon[i*c + j] = '#';                    // then, come back to life
	}
      }
      else{                                          // if u'r alive
	if( !(alive_neig == 2 or alive_neig == 3) ){ // anf if ur hour has come
	  carbon[i*c + j] = '.';                     // then, die
	}
      }
    }
  }  
  return carbon;
}

template <typename T>  // check how many alive cells are in the neighborhood of (i,j). Non-periodic boundary conditions (required for Gosper)
unsigned int check_neig(T m, unsigned int r, unsigned int c,  unsigned int i, unsigned int j){
  unsigned int cont{0};
  std::vector<int> i_list, j_list;
  if( i==0 )        // which rows should I check?
    i_list = {0, 1};
  else if( i == r-1)
    i_list = {-1, 0};
  else
    i_list = {-1, 0, 1};

  if( j==0 )        // which columns should I check?
    j_list = {0, 1};
  else if( j == c-1)
    j_list = {-1, 0};
  else
    j_list = {-1, 0, 1};

  for(auto i_l:i_list){  // check how many alive cells there are
    for(auto j_l:j_list){
      if( !(i_l==0 and j_l==0) ){
        if( m[ (i+i_l)*c + (j+j_l) ] == '#'){
	  cont++;
        }
      }
    }
  }
  return cont;
}

template <typename T>   // print the grid
void show(T m, unsigned int r, unsigned int c){
  
  for(unsigned int k=0; k<6; k++){
    std::cout << std::endl;
  }
  
  for(unsigned int i=0; i<r; i++){
    std::cout << "\t\t";
    for(unsigned int j=0; j<c; j++){
      std::cout << std::setw(3) << m[i*c + j];
    }
    std::cout << std::endl;
  }
   for(unsigned int k=0; k<5; k++){
    std::cout << std::endl;
  }
}
