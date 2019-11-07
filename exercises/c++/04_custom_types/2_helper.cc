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

bool operator==(const date& d1, const date& d2){
  return (d1.day()==d2.day() and d1.month()==d2.month() and d1.year()==d2.year()) ;
}

bool operator!=(const date& d1, const date& d2){
  return !(d1==d2);
}

std::ostream& operator<<(std::ostream& os, const date& d3){
  os << d3.day() << "-" << static_cast<int>(d3.month()) << "-" << d3.year() << std::endl;
  return os;
  }

bool is_leap(const unsigned int y){
    if(y%4 != 0)
      return false;
    else{
      if(y%100 != 0)
	return true;
      else{
	if(y%400 != 0)
	  return false;
	else
	  return true;
      }
    }
}
  

int main(){
  date today{3, months::nov, 2019};
  date tomorrow{4, months::nov, 2019};

  std::cout << "Is this year leap? " << is_leap(today.year()) << std::endl;
  std::cout << "Is today equal to tomorrow? " << (today == tomorrow) << std::endl;
  std::cout << "Is today not equal to tomorrow? " << (today != tomorrow) << std::endl;
  std::cout << "Today is:\n";            // just a couple of tries to check if everything works fine
  std::cout << today;       
  today.add_days(30);
  std::cout << "In 30 days it will be:\n";
  std::cout << today;
  today.add_days(30);
  std::cout << "In 60 days it will be:\n";
  std::cout << today;
  std::cout << "Will that year be leap? " << is_leap(today.year()) << std::endl;
return 0;
}
