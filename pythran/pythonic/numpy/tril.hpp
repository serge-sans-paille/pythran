#ifndef PYTHONIC_NUMPY_TRIL_HPP
#define PYTHONIC_NUMPY_TRIL_HPP

#include "pythonic/include/numpy/tril.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<T, pS> tril(types::ndarray<T, pS> const &expr, int k)
  {
    auto &&expr_shape = expr.shape();
    types::ndarray<T, pS> out(expr_shape, __builtin__::None);
    for (int i = 0; i < std::get<0>(expr_shape); ++i) {
      auto out_i = out[i];
      auto expr_i = expr[i];
      for (long j = 0; j < std::get<1>(expr_shape); ++j)
        if (j - i <= k)
          out_i[j] = expr_i[j];
        else
          out_i[j] = 0;
    }
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(tril)
}
PYTHONIC_NS_END

#endif
