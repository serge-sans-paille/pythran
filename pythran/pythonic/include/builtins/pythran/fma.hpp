#ifndef PYTHONIC_INCLUDE_BUILTINS_PYTHRAN_FMA_HPP
#define PYTHONIC_INCLUDE_BUILTINS_PYTHRAN_FMA_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <xsimd/xsimd.hpp>

PYTHONIC_NS_BEGIN

namespace builtins
{
namespace pythran
{
#ifndef FP_FAST_FMA
    namespace details
    {
      template <class X, class Y, class Z>
      auto fma(X&& x, Y&& y, Z&& z) -> decltype(std::forward<X>(x) * std::forward<Y>(y) + std::forward<Z>(z)) {
        return std::forward<X>(x) * std::forward<Y>(y) + std::forward<Z>(z);
      }
    }
#endif
#define NUMPY_NARY_FUNC_NAME fma
#ifdef FP_FAST_FMA
#define NUMPY_NARY_FUNC_SYM xsimd::fma
#define NUMPY_NARY_EXTRA_METHOD                                                \
    template <class X, class Y, class Z>\
    auto operator()(X&& x, Y&& y, Z&& z) -> decltype(std::forward<X>(x) * std::forward<Y>(y) + std::forward<Z>(z)) {\
      return std::forward<X>(x) * std::forward<Y>(y) + std::forward<Z>(z);\
    }
#else
#define NUMPY_NARY_FUNC_SYM details::fma
#endif

#include "pythonic/include/types/numpy_nary_expr.hpp"
}
}
PYTHONIC_NS_END

#endif
