#ifndef PYTHONIC_NUMPY_TRUEDIVIDE_HPP
#define PYTHONIC_NUMPY_TRUEDIVIDE_HPP

#include "pythonic/include/numpy/true_divide.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic
{

  namespace numpy
  {

// FIXME: this is not always a true_divide...
#define NUMPY_NARY_FUNC_NAME true_divide
#define NUMPY_NARY_FUNC_SYM pythonic::operator_::div
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
