#ifndef PYTHONIC_INCLUDE_NUMPY_SIZE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIZE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto size(E const &e) -> decltype(e.flat_size());

    PROXY_DECL(pythonic::numpy, size)
  }
}

#endif
