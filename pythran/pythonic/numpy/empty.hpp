#ifndef PYTHONIC_NUMPY_EMPTY_HPP
#define PYTHONIC_NUMPY_EMPTY_HPP

#include "pythonic/include/numpy/empty.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <size_t N, class dtype>
    types::ndarray<typename types::numpy_type<dtype>::type, N>
    empty(types::array<long, N> const &shape, dtype d)
    {
      return {shape, __builtin__::None};
    }

    template <class dtype>
    types::ndarray<typename types::numpy_type<dtype>::type, 1> empty(long size,
                                                                     dtype d)
    {
      return empty(types::make_tuple(size), d);
    }

    PROXY_IMPL(pythonic::numpy, empty);
  }
}

#endif
