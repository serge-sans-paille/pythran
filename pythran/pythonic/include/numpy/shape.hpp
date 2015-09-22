#ifndef PYTHONIC_INCLUDE_NUMPY_SHAPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SHAPE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto shape(E const &e) -> decltype(e.shape());

    PROXY_DECL(pythonic::numpy, shape)
  }
}

#endif
