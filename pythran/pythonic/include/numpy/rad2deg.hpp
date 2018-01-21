#ifndef PYTHONIC_INCLUDE_NUMPY_RAD2DEG_HPP
#define PYTHONIC_INCLUDE_NUMPY_RAD2DEG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/indeg.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME rad2deg
#define NUMPY_NARY_FUNC_SYM boost::simd::indeg
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
