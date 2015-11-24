#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDINT_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDINT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {
      template <size_t N>
      types::ndarray<long, N> randint(long min, long max,
                                      types::array<long, N> const &shape);

      long randint(long min, long max);

      long randint(long max);

      auto randint(long min, long max, long size)
          -> decltype(randint(min, max, types::array<long, 1>{{size}}));

      DECLARE_FUNCTOR(pythonic::numpy::random, randint);
    }
  }
}

#endif
