#include <iostream>
#include <iomanip>  // for setw
#include <utility>  // for swap
#include <sstream>  // for istringstream
#include <vector>   // since the dimension can't be known at compile time, std::vectors are prefered to std::arrays

template <class T>
void init(T& mat, unsigned int row, unsigned int col){
  for(unsigned int i{0}; i<row; i++){
    for(unsigned int j{0}; j<col; j++){
      mat.push_back(i*10 + j);
    }
  }
}

template <class T>  
void printm(T&  mat, unsigned int row, unsigned int col){
  for(unsigned int i{0}; i<row; i++){
    for(unsigned int j{0}; j<col; j++){
      std::cout << std::setw(3) << mat[i*col + j];
    }
    std::cout << std::endl;
  }
}

template <class T>
T transpose(T& mat, unsigned int row, unsigned int col){
  if(row == col){
    for(unsigned int i{0}; i<row; i++){
      for(unsigned int j{i+1}; j<col; j++){
	std::swap(mat[i*col + j] , mat[j*col + i]);
      }
    }
    return mat;
  }
  else{
    auto tras = mat;
    for(unsigned int i{0}; i<col; i++){
      for(unsigned int j{0}; j<row; j++){
	tras[i*row + j] = mat[j*col + i];
      }
    }
    return tras;
  }
}

int main(int argc, char* argv[]){
  std::size_t r;
  std::size_t c;
  
  {
  std::istringstream is{argv[1]};
  is >> r;
  std::istringstream is2{argv[2]};
  is2 >> c;
  }

  std::vector<double> mat;
 
  init(mat, r, c);
  std::cout << "Matrix: \n";
  printm(mat, r, c);
  mat = transpose(mat, r, c);
  std::cout << "\nTransposed: \n";
  printm(mat, c, r);  
  
  return 0;}
