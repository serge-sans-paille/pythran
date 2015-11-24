#ifndef PYTHONIC_NUMPY_TAN_HPP
#define PYTHONIC_NUMPY_TAN_HPP

#include "pythonic/include/numpy/tan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/tan.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME tan
#define NUMPY_NARY_FUNC_SYM nt2::tan
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
