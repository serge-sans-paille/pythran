#ifndef PYTHONIC_INCLUDE_NUMPY_ALEN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALEN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    long alen(T &&expr);

    PROXY_DECL(pythonic::numpy, alen);
  }
}

#endif
