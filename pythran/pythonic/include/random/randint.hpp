#ifndef PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP
#define PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/random/randrange.hpp"

namespace pythonic
{

  namespace random
  {

    long randint(long a, long b);

    DECLARE_FUNCTOR(pythonic::random, randint);
  }
}

#endif
