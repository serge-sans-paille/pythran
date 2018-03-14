#ifndef PYTHONIC_SCIPY_SPECIAL_GAMMALN_HPP
#define PYTHONIC_SCIPY_SPECIAL_GAMMALN_HPP

#include "pythonic/include/scipy/special/gammaln.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_traits.hpp"

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
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif
