#ifndef PYTHONIC_RANDOM_SEED_HPP
#define PYTHONIC_RANDOM_SEED_HPP

#include "pythonic/include/random/seed.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/random/random.hpp"

#include <ctime>

namespace pythonic
{

  namespace random
  {
    types::none_type seed(long s)
    {
      __random_generator.seed(s);
      return __builtin__::None;
    }

    types::none_type seed()
    {
      __random_generator.seed(time(nullptr));
      return __builtin__::None;
    }

    DEFINE_FUNCTOR(pythonic::random, seed);
  }
}

#endif
