#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_BYTES_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_BYTES_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      types::str bytes(long length);

      PROXY_DECL(pythonic::numpy::random, bytes);
    }
  }
}

#endif
