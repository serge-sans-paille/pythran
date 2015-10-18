#ifndef PYTHONIC_INCLUDE_NUMPY_ABS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ABS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/abs.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2
{
  constexpr bool abs(bool v);
}

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME abs
#define NUMPY_NARY_FUNC_SYM nt2::abs
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
