#ifndef PYTHONIC_INCLUDE_NUMPY_ONES_HPP
#define PYTHONIC_INCLUDE_NUMPY_ONES_HPP

#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <size_t N, class dtype = functor::float64>
    types::ndarray<typename dtype::type, N>
    ones(types::array<long, N> const &shape, dtype d = dtype());

    template <class dtype = functor::float64>
    types::ndarray<typename dtype::type, 1> ones(long size, dtype d = dtype());

    DECLARE_FUNCTOR(pythonic::numpy, ones);
  }
}

#endif
