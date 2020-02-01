CC = cc

all: libhello.so

libhello.so: hello.c
	$(CC) -shared -fpic -o $@ $< -std=c11

clean:
	rm -f *~ libhello.so

.PHONY: clean all format

format: hello.c
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

# Wanna link c++ and python? you gotta build a C-interface (that must be a shared library) and then call that interface from python. You can't call c++ from python.
