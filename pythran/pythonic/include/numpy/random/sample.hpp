#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_SAMPLE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_SAMPLE_HPP

#include "pythonic/include/numpy/random/random.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      ALIAS_DECL(sample, random);
      PROXY_DECL(pythonic::numpy::random, sample);
    }
  }
}

#endif
