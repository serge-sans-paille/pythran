#ifndef PYTHONIC_NUMPY_RADIANS_HPP
#define PYTHONIC_NUMPY_RADIANS_HPP

#include "pythonic/include/numpy/radians.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME radians
#define NUMPY_NARY_FUNC_SYM boost::simd::inrad
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
