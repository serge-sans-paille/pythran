#ifndef PYTHONIC_INCLUDE_NUMPY_SIGN_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIGN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/sign.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME sign
#define NUMPY_NARY_FUNC_SYM nt2::sign
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
