#ifndef PYTHONIC_INCLUDE_NUMPY_INDICES_HPP
#define PYTHONIC_INCLUDE_NUMPY_INDICES_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/int64.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <size_t N, class dtype = functor::int64>
    types::ndarray<typename dtype::type, N + 1>
    indices(types::array<long, N> const &shape, dtype d = dtype());

    DECLARE_FUNCTOR(pythonic::numpy, indices);
  }
}

#endif
