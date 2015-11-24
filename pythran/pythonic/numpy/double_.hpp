#ifndef PYTHONIC_NUMPY_DOUBLE_HPP
#define PYTHONIC_NUMPY_DOUBLE_HPP

#include "pythonic/include/numpy/double_.hpp"
#include "pythonic/include/numpy/float64.hpp"

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME double_
#define NUMPY_NARY_FUNC_SYM details::float64
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
