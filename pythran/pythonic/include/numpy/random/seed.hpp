#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_SEED_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_SEED_HPP

#include "pythonic/include/numpy/random/generator.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      types::none_type seed(long s);
      types::none_type seed(types::none_type _ = {});

      DECLARE_FUNCTOR(pythonic::numpy::random, seed);
    }
  }
}

#endif
