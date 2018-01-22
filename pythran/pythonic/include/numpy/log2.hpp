#ifndef PYTHONIC_INCLUDE_NUMPY_LOG2_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG2_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/log2.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME log2
#define NUMPY_NARY_FUNC_SYM boost::simd::log2
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
