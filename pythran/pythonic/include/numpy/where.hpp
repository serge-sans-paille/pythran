#ifndef PYTHONIC_INCLUDE_NUMPY_WHERE_HPP
#define PYTHONIC_INCLUDE_NUMPY_WHERE_HPP

#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/numpy/nonzero.hpp"
#include "pythonic/include/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace impl
    {
      template <class E, class F, class G>
      typename __combined<F, G>::type where(E const &cond, F const &true_,
                                            G const &false_);
    }

#define NUMPY_NARY_EXTRA_METHOD                                                \
  template <class E>                                                           \
  auto operator()(E const &expr)->decltype(nonzero{}(expr))                    \
  {                                                                            \
    return nonzero{}(expr);                                                    \
  }

#define NUMPY_NARY_FUNC_NAME where
#define NUMPY_NARY_FUNC_SYM impl::where
#define NUMPY_NARY_RESHAPE_MODE reshape_type
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
