#ifndef PYTHONIC_RANDOM_UNIFORM_HPP
#define PYTHONIC_RANDOM_UNIFORM_HPP

#include "pythonic/include/random/uniform.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"

PYTHONIC_NS_BEGIN

namespace random
{
  double uniform(double a, double b)
  {
    return a + (b - a) * random();
  }

  DEFINE_FUNCTOR(pythonic::random, uniform);
}
PYTHONIC_NS_END

#endif
