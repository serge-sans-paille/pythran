#ifndef PYTHONIC_INCLUDE_NUMPY_RECIPROCAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RECIPROCAL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/rec.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME reciprocal
#define NUMPY_NARY_FUNC_SYM boost::simd::rec
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
