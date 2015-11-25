#ifndef PYTHONIC_INCLUDE_NUMPY_FMIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_FMIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/min.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME fmin
#define NUMPY_NARY_FUNC_SYM nt2::min
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
