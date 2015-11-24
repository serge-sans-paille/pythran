#ifndef PYTHONIC_NUMPY_RANDOM_RANDINT_HPP
#define PYTHONIC_NUMPY_RANDOM_RANDINT_HPP

#include "pythonic/include/numpy/random/randint.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"

#include <random>

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {

      template <size_t N>
      types::ndarray<long, N> randint(long min, long max,
                                      types::array<long, N> const &shape)
      {
        types::ndarray<long, N> result{shape, types::none_type()};
        std::uniform_int_distribution<long> distribution{min, max - 1};
        std::generate(result.fbegin(), result.fend(),
                      [&]() { return distribution(details::generator); });
        return result;
      }

      auto randint(long min, long max, long size)
          -> decltype(randint(min, max, types::array<long, 1>{{size}}))
      {
        return randint(min, max, types::array<long, 1>{{size}});
      }

      long randint(long max)
      {
        return std::uniform_int_distribution<long>{0,
                                                   max - 1}(details::generator);
      }

      long randint(long min, long max)
      {
        return std::uniform_int_distribution<long>{min,
                                                   max - 1}(details::generator);
      }

      DEFINE_FUNCTOR(pythonic::numpy::random, randint);
    }
  }
}

#endif
