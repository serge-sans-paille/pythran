#ifndef PYTHONIC_INCLUDE_NUMPY_COSH_HPP
#define PYTHONIC_INCLUDE_NUMPY_COSH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <xsimd/xsimd.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

#define TRIGO_FUN cosh
#include "pythonic/include/numpy/trigo.hpp"

#define NUMPY_NARY_FUNC_NAME cosh
#define NUMPY_NARY_FUNC_SYM wrapper::cosh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
