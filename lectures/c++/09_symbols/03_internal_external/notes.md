If we used static it would have been an internal linkage: each compilational unit had his own copy.
In c++ const implies static.
Better to use constexpr to force computational effort to be done at compile time.
Instead, if you have to do multilanguage (with c) you have to write static const,
because in c const does not imply static.
If you want to be sure if it's external or internal linkage, do nm -C main.o;
In this way you see some letters: upper case means external linkage, lower case means internal.
If you want internal linkage use static; use extern for global variables (external linkage).
However, the global variables don't need to be defined in a compilation unit to be used, if they have
been defined here like `extern int circle_counter`.
Bad because of typos if you don't do it like this!! use a new header: for example global.h and remember to link it (global.cc and global.o)
