#ifndef PYTHONIC_NUMPY_RANDOM_RANF_HPP
#define PYTHONIC_NUMPY_RANDOM_RANF_HPP

#include "pythonic/include/numpy/random/ranf.hpp"

#include "pythonic/numpy/random/random.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      ALIAS(ranf, random);
      PROXY_IMPL(pythonic::numpy::random, ranf);
    }
  }
}

#endif
