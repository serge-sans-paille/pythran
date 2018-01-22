#ifndef PYTHONIC_NUMPY_FMAX_HPP
#define PYTHONIC_NUMPY_FMAX_HPP

#include "pythonic/include/numpy/fmax.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME fmax
#define NUMPY_NARY_FUNC_SYM boost::simd::max
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
