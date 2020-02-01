#ifndef __constants__
#define __constants__

constexpr double pi{3.14159265358};
const double phi{1.6180339887};

//if we used static it would have been an internal linkage: each compilational unit had his own copy
//in c++ const implies static
//better to use constexpr to force computational effort to be done at compile time
//instead, if you have to do multilanguage (with c) you have to write static const 
//if you want to be sure if it's external or internal linkage, do nm -C main.o; in this way you see some letters: upper case means external linkage, lower means internal
//if you want internal linkage use static; use extern for global variables (external linkage)
//however, the global variables don'thave to be defined in a compilational unit to be used if they has been defined here like 
//extern int circle_counter
//Bad because of typos if you don't do it like this!! use a new header: for example global.h and remember to link it (global.cc and global.o)

#endif
