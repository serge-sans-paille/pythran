#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_SAMPLE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_SAMPLE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/numpy/random/random.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      ALIAS_DECL(random_sample, random);
      PROXY_DECL(pythonic::numpy::random, random_sample);
    }
  }
}

#endif
