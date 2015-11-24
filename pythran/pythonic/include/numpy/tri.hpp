#ifndef PYTHONIC_INCLUDE_NUMPY_TRI_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRI_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/float64.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class dtype = proxy::float64>
    types::ndarray<typename dtype::type, 2> tri(int N, int M = -1, int k = 0,
                                                dtype d = dtype());

    PROXY_DECL(pythonic::numpy, tri)
  }
}

#endif
