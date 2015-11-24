#ifndef PYTHONIC_RANDOM_RANDOM_HPP
#define PYTHONIC_RANDOM_RANDOM_HPP

#include "pythonic/include/random/random.hpp"

#include "pythonic/utils/functor.hpp"
#include <random>

namespace pythonic
{

  namespace random
  {

    double random()
    {
      static std::uniform_real_distribution<> uniform_distrib(0.0, 1.0);
      return uniform_distrib(__random_generator);
    }

    DEFINE_FUNCTOR(pythonic::random, random);
  }
}

#endif
