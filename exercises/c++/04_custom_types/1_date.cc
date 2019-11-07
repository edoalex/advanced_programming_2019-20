#include <iostream>

enum class months{jan=1, feb, mar, apr, may, jun,
		 jul, aug, sep, oct, nov, dec};

class date{
private:
  unsigned int d;
  months m;
  unsigned int y;
  void add_one();     // add one single day to the date
public:
  date(const unsigned int d, months m, const unsigned int y)
    : d{d}, m{m}, y{y}
  {}

  unsigned int const day() const {return d;}
  months const month() const {return m;}
  unsigned int const year() const {return y;}
  void add_days(const unsigned int n);       // add n days to date
  void const print() const{
    std::cout << d << "-" << static_cast<int>(m) << "-" << y << std::endl;
  }
};

void date::add_one(){
    short lim;
    switch(m){
    case months::jan: case months::mar: case months::may: case months::jul:
    case months::aug: case months::oct: case months::dec:
      lim = 31;
      break;
    case months::apr: case months::jun: case months::sep: case months::nov:
      lim = 30;
      break;
    case months::feb:
      lim = 28;
      break;
    }
    if(d < lim)
      ++d;
    else{
      d = 1;
      if(m == months::dec){
	m = months::jan;
	++y;
      }
      else{
	m = months(static_cast<int>(m) + 1);
      }
    }
  }

void date::add_days(const unsigned int n){
  for(auto i=0u; i<n; i++){
    add_one();
  }
}


int main(){
  date today{3, months::nov, 2019};

  std::cout << "Today is:\n";            // just a couple of tries to check if everything works fine
  today.print();       
  today.add_days(30);
  std::cout << "In 30 days it will be:\n";
  today.print();
  today.add_days(30);
  std::cout << "In 60 days it will be:\n";
  today.print();
  return 0;
}
