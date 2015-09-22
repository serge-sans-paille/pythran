#ifndef PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP
#define PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/random/randrange.hpp"

namespace pythonic
{

  namespace random
  {

    long randint(long a, long b);

    PROXY_DECL(pythonic::random, randint);
  }
}

#endif
