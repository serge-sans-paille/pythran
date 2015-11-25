#ifndef PYTHONIC_RANDOM_RANDRANGE_HPP
#define PYTHONIC_RANDOM_RANDRANGE_HPP

#include "pythonic/include/random/randrange.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"

#include <cmath>

namespace pythonic
{

  namespace random
  {
    long randrange(long stop)
    {
      return long(random() * stop);
    }

    long randrange(long start, long stop)
    {
      return start + long(random() * (stop - start));
    }

    long randrange(long start, long stop, long step)
    {
      return start + step * long((random() * (stop - start)) / std::abs(step));
    }

    DEFINE_FUNCTOR(pythonic::random, randrange)
  }
}

#endif
