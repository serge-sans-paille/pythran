#ifndef PYTHONIC_INCLUDE_SCIPY_SPECIAL_GAMMALN_HPP
#define PYTHONIC_INCLUDE_SCIPY_SPECIAL_GAMMALN_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#ifdef USE_BOOST_SIMD
#include <boost/simd/function/gammaln.hpp>
#else
#include <cmath>
#endif

PYTHONIC_NS_BEGIN

namespace scipy
{
  namespace special
  {
#define NUMPY_NARY_FUNC_NAME gammaln
#ifdef USE_BOOST_SIMD
#define NUMPY_NARY_FUNC_SYM boost::simd::gammaln
#else
#define NUMPY_NARY_FUNC_SYM std::lgamma
#endif

#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif
