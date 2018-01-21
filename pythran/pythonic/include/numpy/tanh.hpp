#ifndef PYTHONIC_INCLUDE_NUMPY_TANH_HPP
#define PYTHONIC_INCLUDE_NUMPY_TANH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/tanh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
#define NUMPY_NARY_FUNC_NAME tanh
#define NUMPY_NARY_FUNC_SYM boost::simd::tanh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
