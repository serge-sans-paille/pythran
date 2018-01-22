#ifndef PYTHONIC_NUMPY_DEGREES_HPP
#define PYTHONIC_NUMPY_DEGREES_HPP

#include "pythonic/include/numpy/degrees.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME degrees
#define NUMPY_NARY_FUNC_SYM boost::simd::indeg
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
