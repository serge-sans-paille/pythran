#ifndef PYTHONIC_INCLUDE_NUMPY_RIGHTSHIFT_HPP
#define PYTHONIC_INCLUDE_NUMPY_RIGHTSHIFT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include "pythonic/include/operator_/rshift.hpp"

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME right_shift
#define NUMPY_NARY_FUNC_SYM operator_::rshift
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
