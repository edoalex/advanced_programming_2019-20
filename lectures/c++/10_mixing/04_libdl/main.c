#include <dlfcn.h>

int main(int argc, char* argv[]) {
  void* handle; /* handle for dynamic object */
  void (*hi)(); /* function pointer for symbol */
  int (*rep)(char*);
  handle = dlopen("./libhello.so", RTLD_LAZY);
  if (handle) {
    hi = (void (*)())dlsym(handle, "hello");
    // cause hello takes no args and return void
    // I'm looking for hello symbols 
    (*hi)();
    rep = (int (*)(char*))dlsym(handle, "repeat");
    // cause repeat takes a char* and return an int
    rep("I dont't care what fox says");
    dlclose(handle);
  }
  return 0;
}
