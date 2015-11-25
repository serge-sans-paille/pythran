#ifndef PYTHONIC_INCLUDE_NUMPY_LOG2_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG2_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/log2.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME log2
#define NUMPY_NARY_FUNC_SYM nt2::log2
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
