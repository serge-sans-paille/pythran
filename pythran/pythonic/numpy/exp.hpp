#ifndef PYTHONIC_NUMPY_EXP_HPP
#define PYTHONIC_NUMPY_EXP_HPP

#include "pythonic/include/numpy/exp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/exp.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME exp
#define NUMPY_NARY_FUNC_SYM nt2::exp
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
