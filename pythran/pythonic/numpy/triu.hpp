#ifndef PYTHONIC_NUMPY_TRIU_HPP
#define PYTHONIC_NUMPY_TRIU_HPP

#include "pythonic/include/numpy/triu.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<T, pS> triu(types::ndarray<T, pS> const &expr, int k)
  {
    auto &&expr_shape = expr.shape();
    types::ndarray<T, pS> out(expr_shape, __builtin__::None);
    for (int i = 0; i < std::get<0>(expr_shape); ++i)
      for (long j = 0; j < std::get<1>(expr_shape); ++j)
        if (j - i >= k)
          out[i][j] = expr[i][j];
        else
          out[i][j] = 0;
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(triu)
}
PYTHONIC_NS_END

#endif
