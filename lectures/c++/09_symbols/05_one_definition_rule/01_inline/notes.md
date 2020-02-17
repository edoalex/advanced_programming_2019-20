Functions are external linked by default; this is a problem if we only write void dummy() because when we link the various libraries we have multiple definition of dummy().
*Solution*: use `static` or `inline` (as here seen)
*Difference*: with `inline` you suggest the compiler not to put a jump to that function, but to copy and paste the content of the function,
Use it only with small functions! By the way, it’s only a suggestion, the compiler can do what he wants: he can choose not to inline inlined function or inline not inlined functions;
`inline` implies internal linkage in c++, in c it's not implied, you have to put `static` too to get internal linkage.
Indeed, if you use `inline` in the dummy() function of func.h, the symbols of the dummy function in the other (src1, src2) object files will be marked with W, meaning it's a *weak* symbol