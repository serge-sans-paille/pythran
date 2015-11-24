#ifndef PYTHONIC_INCLUDE_NUMPY_ARCCOS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCCOS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/acos.hpp>

namespace nt2
{
  double acos(long l);
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME arccos
#define NUMPY_NARY_FUNC_SYM nt2::acos
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
