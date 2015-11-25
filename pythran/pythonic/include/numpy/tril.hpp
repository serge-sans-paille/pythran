#ifndef PYTHONIC_INCLUDE_NUMPY_TRIL_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRIL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    types::ndarray<T, 2> tril(types::ndarray<T, 2> const &expr, int k = 0);

    NUMPY_EXPR_TO_NDARRAY0_DECL(tril)
    DECLARE_FUNCTOR(pythonic::numpy, tril)
  }
}

#endif
