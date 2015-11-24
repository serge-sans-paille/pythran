#ifndef PYTHONIC_NUMPY_ROT90_HPP
#define PYTHONIC_NUMPY_ROT90_HPP

#include "pythonic/include/numpy/rot90.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> rot90(types::ndarray<T, N> const &expr, int k)
    {
      if (k % 4 == 0)
        return copy(expr);
      types::array<long, N> shape;
      auto &&expr_shape = expr.shape();
      std::copy(expr_shape.begin(), expr_shape.end(), shape.begin());
      if (k % 4 != 2)
        std::swap(shape[0], shape[1]);
      types::ndarray<T, N> out(shape, __builtin__::None);
      auto &&out_shape = out.shape();
      if (k % 4 == 1) {
        for (int i = 0; i < out_shape[1]; ++i)
          for (int j = 0; j < out_shape[0]; ++j)
            out[out_shape[0] - 1 - j][i] = expr[i][j];
      } else if (k % 4 == 2) {
        for (int i = 0; i < out_shape[1]; ++i)
          for (int j = 0; j < out_shape[0]; ++j)
            out[out_shape[0] - 1 - j][out_shape[1] - 1 - i] = expr[j][i];
      } else {
        for (int i = 0; i < out_shape[1]; ++i)
          for (int j = 0; j < out_shape[0]; ++j)
            out[j][out_shape[1] - 1 - i] = expr[i][j];
      }
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(rot90)
    DEFINE_FUNCTOR(pythonic::numpy, rot90);
  }
}

#endif
