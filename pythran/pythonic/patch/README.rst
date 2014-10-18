=================
Pythran std patch
=================

The implementation of std::complex is very slow, due to the complex limited
range (see `-fcx-limited-range`) feature. Numpy does not implement it, so we
have to conform to numpy's version. the only way I (SG) found to fix this is to
monkey-patch `std::complex`. Inheritence or defining a new class does not work
because nt2 assumes we use std::complex.

The original source is libcxx, the diff is rather small (mostly removed libcxx
internal stuff and use numpy-compliant version of the multiuply operator). The
speedup is very interesting!

GCC does provide the flag `-fcx-limited-range` to fix the issue in a more
elgant way, but it is not supported by clang.
