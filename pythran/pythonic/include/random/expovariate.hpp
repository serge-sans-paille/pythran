#ifndef PYTHONIC_INCLUDE_RANDOM_EXPOVARIATE_HPP
#define PYTHONIC_INCLUDE_RANDOM_EXPOVARIATE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    double expovariate(double l);

    PROXY_DECL(pythonic::random, expovariate);
  }
}

#endif
