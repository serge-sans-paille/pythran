#ifndef PYTHONIC_NUMPY_RAD2DEG_HPP
#define PYTHONIC_NUMPY_RAD2DEG_HPP

#include "pythonic/include/numpy/rad2deg.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/indeg.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME rad2deg
#define NUMPY_NARY_FUNC_SYM nt2::indeg
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
