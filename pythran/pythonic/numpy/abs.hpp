#ifndef PYTHONIC_NUMPY_ABS_HPP
#define PYTHONIC_NUMPY_ABS_HPP

#include "pythonic/include/numpy/abs.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

#define NUMPY_NARY_FUNC_NAME abs
#ifdef USE_XSIMD
#define NUMPY_NARY_FUNC_SYM wrapper::abs
#else
#define NUMPY_NARY_FUNC_SYM std::abs
#endif
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
