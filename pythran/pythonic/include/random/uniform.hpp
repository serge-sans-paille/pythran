#ifndef PYTHONIC_INCLUDE_RANDOM_UNIFORM_HPP
#define PYTHONIC_INCLUDE_RANDOM_UNIFORM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    double uniform(double a, double b);

    DECLARE_FUNCTOR(pythonic::random, uniform);
  }
}

#endif
