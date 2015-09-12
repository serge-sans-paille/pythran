#ifndef PYTHONIC_INCLUDE_RANDOM_GAUSS_HPP
#define PYTHONIC_INCLUDE_RANDOM_GAUSS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {

    double gauss(double mu, double sigma);

    PROXY_DECL(pythonic::random, gauss);
  }
}

#endif
