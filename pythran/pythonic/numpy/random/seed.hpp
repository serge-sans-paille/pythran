#ifndef PYTHONIC_NUMPY_RANDOM_SEED_HPP
#define PYTHONIC_NUMPY_RANDOM_SEED_HPP

#include "pythonic/include/numpy/random/seed.hpp"
#include "pythonic/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace random
  {

    types::none_type seed(long s)
    {
      details::generator.seed(s);
      return __builtin__::None;
    }

    types::none_type seed(types::none_type)
    {
      details::generator.seed();
      return __builtin__::None;
    }

    DEFINE_FUNCTOR(pythonic::numpy::random, seed);
  }
}

PYTHONIC_NS_END

#endif
