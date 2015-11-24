#ifndef PYTHONIC_NUMPY_INVERT_HPP
#define PYTHONIC_NUMPY_INVERT_HPP

#include "pythonic/include/numpy/invert.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/invert.hpp"

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME invert
#define NUMPY_NARY_FUNC_SYM operator_::invert
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
