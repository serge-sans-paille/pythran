#ifndef PYTHONIC_INCLUDE_NUMPY_COPYTO_HPP
#define PYTHONIC_INCLUDE_NUMPY_COPYTO_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{
  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> copyto(types::ndarray<T, N> &out,
                                types::ndarray<T, N> const &a);

    PROXY_DECL(pythonic::numpy, copyto);
  }
}

#endif
