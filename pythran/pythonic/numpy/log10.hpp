#ifndef PYTHONIC_NUMPY_LOG10_HPP
#define PYTHONIC_NUMPY_LOG10_HPP

#include "pythonic/include/numpy/log10.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/log10.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME log10
#define NUMPY_NARY_FUNC_SYM nt2::log10
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
