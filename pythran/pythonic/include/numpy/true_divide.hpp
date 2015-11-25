#ifndef PYTHONIC_INCLUDE_NUMPY_TRUEDIVIDE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRUEDIVIDE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/operator_/div.hpp"

namespace pythonic
{

  namespace numpy
  {

// FIXME: this is not always a true_divide...
#define NUMPY_NARY_FUNC_NAME true_divide
#define NUMPY_NARY_FUNC_SYM pythonic::operator_::div
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
