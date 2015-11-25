#ifndef PYTHONIC_NUMPY_SINH_HPP
#define PYTHONIC_NUMPY_SINH_HPP

#include "pythonic/include/numpy/sinh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/sinh.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME sinh
#define NUMPY_NARY_FUNC_SYM nt2::sinh
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
