#ifndef PYTHONIC_NUMPY_MULTIPLY_HPP
#define PYTHONIC_NUMPY_MULTIPLY_HPP

#include "pythonic/include/numpy/multiply.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/mul.hpp"

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME multiply
#define NUMPY_NARY_FUNC_SYM pythonic::operator_::mul
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
