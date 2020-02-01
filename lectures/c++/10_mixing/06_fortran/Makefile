CXX = c++
CC = cc
FCC = gfortran
EXE-C = c-exe
EXE-CXX = cpp-exe

all: $(EXE-C) $(EXE-CXX)

$(EXE-C): c-main.o f-sum.o
	$(CC) $^ -o $@

$(EXE-CXX): cpp-main.o f-sum.o
	$(CXX) $^ -o $@

cpp-main.o: cpp-main.cpp
	$(CXX) $< -c -o $@

c-main.o: c-main.c
	$(CC) $< -c -o $@

f-sum.o: f-sum.f90
	$(FCC) -c $< -o $@

clean:
	rm -f *~ *.o $(EXE-C) $(EXE-CXX)

.PHONY: all clean format

format: c-main.c cpp-main.cpp
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"


# if yoy want to use Fortran functions, u gotta call them in C/C++ with a trailing underscore (ex sum_abs_)
# moreover, in Fortran function arguments are always pointers (put pointers everywhere)! Remember this when writing C/C++ part of the code
