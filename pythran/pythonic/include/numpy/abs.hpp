#ifndef PYTHONIC_INCLUDE_NUMPY_ABS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ABS_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

#define NUMPY_NARY_FUNC_NAME abs
#define NUMPY_NARY_FUNC_SYM std::abs
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
