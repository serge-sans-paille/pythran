#ifndef PYTHONIC_NUMPY_ADD_REDUCE_HPP
#define PYTHONIC_NUMPY_ADD_REDUCE_HPP

#include "pythonic/include/numpy/add/reduce.hpp"
#define UFUNC_NAME add
#define UFUNC_INAME iadd
#include "pythonic/numpy/ufunc_reduce.hpp"
#undef UFUNC_NAME
#undef UFUNC_INAME

#endif
