#ifndef PYTHONIC_RANDOM_GAUSS_HPP
#define PYTHONIC_RANDOM_GAUSS_HPP

#include "pythonic/include/random/gauss.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"

PYTHONIC_NS_BEGIN

namespace random
{

  double gauss(double mu, double sigma)
  {
    return std::normal_distribution<>(mu, sigma)(__random_generator);
  }

  DEFINE_FUNCTOR(pythonic::random, gauss);
}
PYTHONIC_NS_END

#endif
