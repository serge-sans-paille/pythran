#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_FLATTEN_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_FLATTEN_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {
      template <class T, size_t N>
      types::ndarray<T, 1> flatten(types::ndarray<T, N> const &a);

      NUMPY_EXPR_TO_NDARRAY0_DECL(flatten);
      DECLARE_FUNCTOR(pythonic::numpy::ndarray, flatten);
    }
  }
}

#endif
