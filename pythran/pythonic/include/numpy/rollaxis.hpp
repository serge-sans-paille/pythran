#ifndef PYTHONIC_INCLUDE_NUMPY_ROLLAXIS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROLLAXIS_HPP

#include "pythonic/include/numpy/transpose.hpp"
#include "pythonic/include/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> rollaxis(types::ndarray<T, N> const &a, long axis,
                                  long start = 0);

    NUMPY_EXPR_TO_NDARRAY0_DECL(rollaxis);
    DECLARE_FUNCTOR(pythonic::numpy, rollaxis);
  }
}

#endif
