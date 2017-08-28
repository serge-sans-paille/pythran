#ifndef PYTHONIC_INCLUDE_NUMPY_FLIP_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLIP_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> flip(types::ndarray<T, N> const &expr, long axis);

    NUMPY_EXPR_TO_NDARRAY0_DECL(flip);
    DECLARE_FUNCTOR(pythonic::numpy, flip);
  }
}

#endif
