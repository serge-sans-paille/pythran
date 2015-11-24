#ifndef PYTHONIC_NUMPY_RAVEL_HPP
#define PYTHONIC_NUMPY_RAVEL_HPP

#include "pythonic/include/numpy/ravel.hpp"

#include "pythonic/numpy/reshape.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, 1> ravel(types::ndarray<T, N> const &expr)
    {
      return reshape(expr, types::array<long, 1>{{expr.flat_size()}});
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(ravel);
    DEFINE_FUNCTOR(pythonic::numpy, ravel);
  }
}

#endif
