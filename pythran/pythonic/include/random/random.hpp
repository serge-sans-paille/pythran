#ifndef PYTHONIC_INCLUDE_RANDOM_RANDOM_HPP
#define PYTHONIC_INCLUDE_RANDOM_RANDOM_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <random>

namespace pythonic
{

  namespace random
  {

    static std::mt19937 __random_generator;

    double random();

    PROXY_DECL(pythonic::random, random);
  }
}

#endif
