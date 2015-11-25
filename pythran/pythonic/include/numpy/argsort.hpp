#ifndef PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<long, N> argsort(types::ndarray<T, N> const &a);

    NUMPY_EXPR_TO_NDARRAY0_DECL(argsort);

    DECLARE_FUNCTOR(pythonic::numpy, argsort);
  }
}

#endif
