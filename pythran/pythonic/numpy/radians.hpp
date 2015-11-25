#ifndef PYTHONIC_NUMPY_RADIANS_HPP
#define PYTHONIC_NUMPY_RADIANS_HPP

#include "pythonic/include/numpy/radians.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/inrad.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME radians
#define NUMPY_NARY_FUNC_SYM nt2::inrad
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
