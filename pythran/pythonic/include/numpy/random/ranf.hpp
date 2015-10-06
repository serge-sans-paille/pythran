#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANF_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANF_HPP

#include "pythonic/include/numpy/random/random.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      ALIAS_DECL(ranf, random);
      PROXY_DECL(pythonic::numpy::random, ranf);
    }
  }
}

#endif
