#ifndef PYTHONIC_NUMPY_RANDOM_SEED_HPP
#define PYTHONIC_NUMPY_RANDOM_SEED_HPP

#include "pythonic/include/numpy/random/seed.hpp"
#include "pythonic/builtins/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace random
  {

    types::none_type seed(long s)
    {
      details::generator.seed(s);
      return builtins::None;
    }

    types::none_type seed(types::none_type)
    {
      details::generator.seed();
      return builtins::None;
    }
  }
}

PYTHONIC_NS_END

#endif
