#ifndef PYTHONIC_NUMPY_TRIU_HPP
#define PYTHONIC_NUMPY_TRIU_HPP

#include "pythonic/include/numpy/triu.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    types::ndarray<T, 2> triu(types::ndarray<T, 2> const &expr, int k)
    {
      auto &&expr_shape = expr.shape();
      types::ndarray<T, 2> out(expr_shape, __builtin__::None);
      for (int i = 0; i < expr_shape[0]; ++i)
        for (long j = 0; j < expr_shape[1]; ++j)
          if (j - i >= k)
            out[i][j] = expr[i][j];
          else
            out[i][j] = 0;
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(triu)
    DEFINE_FUNCTOR(pythonic::numpy, triu)
  }
}

#endif
