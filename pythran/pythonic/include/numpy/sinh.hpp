#ifndef PYTHONIC_INCLUDE_NUMPY_SINH_HPP
#define PYTHONIC_INCLUDE_NUMPY_SINH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/sinh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME sinh
#define NUMPY_NARY_FUNC_SYM boost::simd::sinh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
