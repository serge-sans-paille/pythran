#ifndef PYTHONIC_NUMPY_EXPM1_HPP
#define PYTHONIC_NUMPY_EXPM1_HPP

#include "pythonic/include/numpy/expm1.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/expm1.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME expm1
#define NUMPY_NARY_FUNC_SYM nt2::expm1
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
