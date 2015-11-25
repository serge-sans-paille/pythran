#ifndef PYTHONIC_NUMPY_ZEROS_HPP
#define PYTHONIC_NUMPY_ZEROS_HPP

#include "pythonic/include/numpy/zeros.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <size_t N, class dtype>
    types::ndarray<typename dtype::type, N>
    zeros(types::array<long, N> const &shape, dtype d)
    {
      using T = typename dtype::type;
      // use calloc even if we have a non integer type. This looks ok on modern
      // architecture, although not really standard
      auto *buffer = (T *)calloc(std::accumulate(shape.begin(), shape.end(), 1L,
                                                 std::multiplies<long>()),
                                 sizeof(T));
      return types::ndarray<T, N>{buffer, shape.data()};
    }

    template <class dtype>
    types::ndarray<typename dtype::type, 1> zeros(long size, dtype d)
    {
      return zeros(types::make_tuple(size), d);
    }

    DEFINE_FUNCTOR(pythonic::numpy, zeros);
  }
}

#endif
