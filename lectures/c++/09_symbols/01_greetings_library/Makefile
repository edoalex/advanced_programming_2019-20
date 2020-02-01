# Makefile:
# target: dep1 dep2 dep3
#	action1
#	action2
##
# if you don't want makefile to echo the command (like in c++....) you put a @ before the command

# make -B force  recompilation
# make -j number_of_processors+1	execute  in parallel
# make -n prints the actions but don't execute them




CXX = c++
LANG = ENGLISH

SRC = src/greetings.cc src/conclusion.cc
OBJ = $(SRC:.cc=.o)

# order of target-blocks (apart from the first one) doesn't matter

all: libgreetings.so

# all: libgreetings.so is a prerequisite. It's the only rule executed, but in practice it executes
# all the ones that are needed to obtain libgreetings.so (and checks if it's up to date before executing it)

libgreetings.so: $(OBJ)
	$(CXX) -shared -o $@ $^

# by convention $@ is the name of the target, $^ is the name of all the dependencies

%.o:%.cc
	$(CXX) -fpic -D$(LANG) -o $@ -c $< -Iinclude

# $< is the first dependency; when you use % the file to be compiled is $<; take it as a rule

src/greetings.o: include/greetings.h

# in this way you say to the makefile that it has to generate again greetings.o if greetings.h is changed (of course)

src/conclusion.o: include/conclusion.h

format: $(SRC) include/greetings.h include/conclusion.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	@rm -f *~ */*~ libgreetings.so src/*.o

.PHONY: clean all format

# .PHONY you execute the following target independently of the fact that it is already present or not
