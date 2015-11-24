#ifndef PYTHONIC_INCLUDE_RANDOM_GAUSS_HPP
#define PYTHONIC_INCLUDE_RANDOM_GAUSS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {

    double gauss(double mu, double sigma);

    DECLARE_FUNCTOR(pythonic::random, gauss);
  }
}

#endif
