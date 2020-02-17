Given the src file, if you compile it you obtain the object file, if you link one or more object files, you obtain the binary; if the binary has a main, it's an executable, otherwise it's a library
Compilation is the longer process between the two, but it can be done in parallel with a makefile (not in the command line)

#### To create object file
c++ -c src/greetings.cc -o src/greetings.o -I include -I another_folder_with_header -fPIC
PIC = position independent code

#### To use object files to create a shared library
c++ greetings.o conclusion.o -shared -o libgreetings.so

#### About Makefile

make -B force  recompilation
make -j number_of_processors+1	execute  in parallel
make -n prints the actions but don't execute them





need to export the LD_LIBRARY_PATH to run the executable, otherwise he can't find the shared library:
export LD_LIBRARY_PATH=../01_greetings_library:$LD_LIBRARY_PATH

