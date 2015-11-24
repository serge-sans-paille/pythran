#ifndef PYTHONIC_INCLUDE_NUMPY_RESIZE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RESIZE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, 1> resize(types::ndarray<T, N> const &expr,
                                long new_shape);

    template <class T, size_t N, size_t M>
    types::ndarray<T, M> resize(types::ndarray<T, N> const &expr,
                                types::array<long, M> const &new_shape);

    NUMPY_EXPR_TO_NDARRAY0_DECL(resize);
    DECLARE_FUNCTOR(pythonic::numpy, resize);
  }
}

#endif
