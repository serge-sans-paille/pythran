#ifndef PYTHONIC_INCLUDE_NUMPY_POWER_HPP
#define PYTHONIC_INCLUDE_NUMPY_POWER_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <nt2/include/functions/pow.hpp>

namespace nt2
{
  // See https://github.com/MetaScale/nt2/issues/794
  double pow(long n, double m);
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME power
#define NUMPY_NARY_FUNC_SYM nt2::pow
// no need to adapt_type here, as it may turn a**2 into a**2.f
#define NUMPY_NARY_RESHAPE_MODE reshape_type
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
