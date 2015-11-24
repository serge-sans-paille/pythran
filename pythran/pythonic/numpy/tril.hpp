#ifndef PYTHONIC_NUMPY_TRIL_HPP
#define PYTHONIC_NUMPY_TRIL_HPP

#include "pythonic/include/numpy/tril.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    types::ndarray<T, 2> tril(types::ndarray<T, 2> const &expr, int k)
    {
      auto &&expr_shape = expr.shape();
      types::ndarray<T, 2> out(expr_shape, __builtin__::None);
      for (int i = 0; i < expr_shape[0]; ++i) {
        auto out_i = out[i];
        auto expr_i = expr[i];
        for (long j = 0; j < expr_shape[1]; ++j)
          if (j - i <= k)
            out_i[j] = expr_i[j];
          else
            out_i[j] = 0;
      }
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(tril)
    DEFINE_FUNCTOR(pythonic::numpy, tril)
  }
}

#endif
