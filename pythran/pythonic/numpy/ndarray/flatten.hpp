#ifndef PYTHONIC_NUMPY_NDARRAY_FLATTEN_HPP
#define PYTHONIC_NUMPY_NDARRAY_FLATTEN_HPP

#include "pythonic/include/numpy/ndarray/flatten.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {
      template <class T, size_t N>
      types::ndarray<T, 1> flatten(types::ndarray<T, N> const &a)
      {
        return {a.mem, types::array<long, 1>{{a.flat_size()}}};
      }

      NUMPY_EXPR_TO_NDARRAY0_IMPL(flatten);
      DEFINE_FUNCTOR(pythonic::numpy::ndarray, flatten);
    }
  }
}

#endif
