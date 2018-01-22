#ifndef PYTHONIC_INCLUDE_NUMPY_LOG_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/log.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME log
#define NUMPY_NARY_FUNC_SYM boost::simd::log
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
