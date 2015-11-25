#ifndef PYTHONIC_RANDOM_EXPOVARIATE_HPP
#define PYTHONIC_RANDOM_EXPOVARIATE_HPP

#include "pythonic/include/random/expovariate.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    double expovariate(double l)
    {
      return std::exponential_distribution<>(l)(__random_generator);
    }

    DEFINE_FUNCTOR(pythonic::random, expovariate);
  }
}

#endif
