#ifndef PYTHONIC_INCLUDE_NUMPY_ARGWHERE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGWHERE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    typename types::ndarray<long, 2> argwhere(E const &expr);

    PROXY_DECL(pythonic::numpy, argwhere);
  }
}

#endif
