#ifndef PYTHONIC_NUMPY_DEG2RAD_HPP
#define PYTHONIC_NUMPY_DEG2RAD_HPP

#include "pythonic/include/numpy/deg2rad.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/inrad.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME deg2rad
#define NUMPY_NARY_FUNC_SYM nt2::inrad
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
