#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_BYTES_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_BYTES_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      types::str bytes(long length);

      DECLARE_FUNCTOR(pythonic::numpy::random, bytes);
    }
  }
}

#endif
