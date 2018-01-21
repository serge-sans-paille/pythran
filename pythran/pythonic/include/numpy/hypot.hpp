#ifndef PYTHONIC_INCLUDE_NUMPY_HYPOT_HPP
#define PYTHONIC_INCLUDE_NUMPY_HYPOT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/hypot.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME hypot
#define NUMPY_NARY_FUNC_SYM boost::simd::hypot
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
