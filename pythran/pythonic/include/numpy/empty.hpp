#ifndef PYTHONIC_INCLUDE_NUMPY_EMPTY_HPP
#define PYTHONIC_INCLUDE_NUMPY_EMPTY_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_type.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <size_t N, class dtype = double>
    types::ndarray<typename types::numpy_type<dtype>::type, N>
    empty(types::array<long, N> const &shape, dtype d = dtype());

    template <class dtype = double>
    types::ndarray<typename types::numpy_type<dtype>::type, 1>
    empty(long size, dtype d = dtype());

    PROXY_DECL(pythonic::numpy, empty);
  }
}

#endif
