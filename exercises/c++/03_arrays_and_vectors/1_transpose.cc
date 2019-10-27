#include <iostream>
#include <iomanip>
#include <array>
#include <utility>

template <class T>
void init(T& mat, unsigned int row, unsigned int col){
  for(unsigned int i{0}; i<row; i++){
    for(unsigned int j{0}; j<col; j++){
      mat[i*col + j] = i*10 + j;
    }
  }
}

template <std::size_t dim>       //other way to solve the dim problem (other than template <class T> and then printm(T& mat, ...) )
void printm(std::array<double, dim>&  mat, unsigned int row, unsigned int col){
  for(unsigned int i{0}; i<row; i++){
    for(unsigned int j{0}; j<col; j++){
      std::cout << std::setw(3) << mat[i*col + j];
    }
    std::cout << std::endl;
  }
}

template <class T>
T transpose(T& mat, unsigned int row, unsigned int col){    // if the matrix is square, the algorithm for rectangular matrices
  if(row == col){                                           // is fine too, but the one that is executed in the square case is more
    for(unsigned int i{0}; i<row; i++){                     // memory efficient
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

int main(){
  const unsigned int r{3};
  const unsigned int c{6};
  std::array<double, r*c> mat{};
 
  init(mat, r, c);
  std::cout << "Matrix: \n";
  printm(mat, r, c);
  mat = transpose(mat, r, c);
  std::cout << "\nTransposed: \n";
  printm(mat, c, r);  
  
  return 0;}
