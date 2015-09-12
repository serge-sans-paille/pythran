#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAY2STRING_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAY2STRING_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    types::str array2string(E &&a);

    PROXY_DECL(pythonic::numpy, array2string);
  }
}

#endif
