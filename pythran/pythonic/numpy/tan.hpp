#ifndef PYTHONIC_NUMPY_TAN_HPP
#define PYTHONIC_NUMPY_TAN_HPP

#include "pythonic/include/numpy/tan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME tan
#define NUMPY_NARY_FUNC_SYM boost::simd::tan
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
