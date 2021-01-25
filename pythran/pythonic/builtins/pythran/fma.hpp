#ifndef PYTHONIC_PYTHRAN_BUILTINS_FMA_HPP
#define PYTHONIC_PYTHRAN_BUILTINS_FMA_HPP

#include "pythonic/include/builtins/pythran/fma.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
namespace pythran
{
#define NUMPY_NARY_FUNC_NAME fma
#ifdef FP_FAST_FMA
#define NUMPY_NARY_FUNC_SYM xsimd::fma
#else
#define NUMPY_NARY_FUNC_SYM details::fma
#endif
#include "pythonic/types/numpy_nary_expr.hpp"
}
}
PYTHONIC_NS_END

#endif
