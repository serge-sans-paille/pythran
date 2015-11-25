#ifndef PYTHONIC_INCLUDE_RANDOM_EXPOVARIATE_HPP
#define PYTHONIC_INCLUDE_RANDOM_EXPOVARIATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    double expovariate(double l);

    DECLARE_FUNCTOR(pythonic::random, expovariate);
  }
}

#endif
