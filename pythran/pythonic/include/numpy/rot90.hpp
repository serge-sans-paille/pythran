#ifndef PYTHONIC_INCLUDE_NUMPY_ROT90_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROT90_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> rot90(types::ndarray<T, N> const &expr, int k = 1);

    NUMPY_EXPR_TO_NDARRAY0_DECL(rot90)
    DECLARE_FUNCTOR(pythonic::numpy, rot90);
  }
}

#endif
