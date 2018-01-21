#ifndef PYTHONIC_INCLUDE_SCIPY_SPECIAL_GAMMA_HPP
#define PYTHONIC_INCLUDE_SCIPY_SPECIAL_GAMMA_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/gamma.hpp>

PYTHONIC_NS_BEGIN

namespace scipy
{
  namespace special
  {

#define NUMPY_NARY_FUNC_NAME gamma
#define NUMPY_NARY_FUNC_SYM boost::simd::gamma
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif
