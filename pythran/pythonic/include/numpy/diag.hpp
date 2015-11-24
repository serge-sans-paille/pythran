#ifndef PYTHONIC_INCLUDE_NUMPY_DIAG_HPP
#define PYTHONIC_INCLUDE_NUMPY_DIAG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    types::ndarray<T, 1> diag(types::ndarray<T, 2> const &a, long k = 0);

    template <class T>
    types::ndarray<T, 2> diag(types::ndarray<T, 1> const &a, long k = 0);

    template <class T>
    auto diag(types::list<T> const &a, long k = 0)
        -> decltype(diag(asarray(a), k));

    NUMPY_EXPR_TO_NDARRAY0_DECL(diag);
    DECLARE_FUNCTOR(pythonic::numpy, diag);
  }
}

#endif
