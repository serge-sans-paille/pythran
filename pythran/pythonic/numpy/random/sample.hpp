#ifndef PYTHONIC_NUMPY_RANDOM_SAMPLE_HPP
#define PYTHONIC_NUMPY_RANDOM_SAMPLE_HPP

#include "pythonic/include/numpy/random/sample.hpp"

#include "pythonic/numpy/random/random.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      ALIAS(sample, random);
      PROXY_IMPL(pythonic::numpy::random, sample);
    }
  }
}

#endif
