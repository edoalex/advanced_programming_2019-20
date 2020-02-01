CC = cc
CXX = c++
EXE = exe

all: $(EXE)

$(EXE): hello.o main.o
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) $< -c -o $@

hello.o: hello.c hello.h
	$(CC) -c $< -o $@

clean:
	rm -f *~ *.o $(EXE)

.PHONY: all clean format

format: hello.c hello.h main.cpp 
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

# how to use c functions in c++ code
# to link, always use the linker of the language of the main function
# if in main I don't write anything (before main), c++ compiler will complain that function has not been defined
# therefore I add #include "hello.h", and the compiler will not complain anymore
# but this tiime the linker will complain! Why? Because it's a c function, compiled with c++ has a different symbolo from the same function in the hello.o file
# how to solve it? write also extern "C" { #include "hello.h"}.
# include is for the compiler, extern is for the linker

# the extern in main could also be avoided, beacuse function by default have external linkage

# linker must also link the library -lstdc++ if I wanna use some c++ libraries
# c++ linker automatically link against c libraries (not the opposite)

# how compile works:
# [SRC] --(language dependent)-> [IL] --> [opt] --> [ass] --> [.o]
# IL = intermediate language   opt = optimized code    ass = assembly
# it's like google translator works at the beginning and then it's the same for all languages (even though it depends on compiiler used)
# .o is universal, language is ELF

# class_c_interface.cpp c++ source and class_c_interface.h c library
# __cplusplus is a Macro automatically exported from any c++ compiler
