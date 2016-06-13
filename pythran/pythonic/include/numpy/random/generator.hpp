#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_GENERATOR_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_GENERATOR_HPP

#include <random>

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      namespace details
      {
        // Found by reading Numpy source code RNG values
        // in (random/mtrand/randomkit.c),
        // but the random generator type is not explicitly mentioned.
        using default_numpy_generator_t = std::mt19937;
        std::random_device rd;
        default_numpy_generator_t generator(rd());
      }
    }
  }
}

#endif
