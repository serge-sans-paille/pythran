#ifndef PYTHONIC_NUMPY_RANDOM_POISSON_HPP
#define PYTHONIC_NUMPY_RANDOM_POISSON_HPP

#include "pythonic/include/numpy/random/generator.hpp"
#include "pythonic/include/numpy/random/poisson.hpp"

#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>
#include <random>

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {

    template <size_t N>
    types::ndarray<double, N> poisson(double lam,
                                      types::array<long, N> const &shape)
    {
      types::ndarray<double, N> result{shape, types::none_type()};
      std::poisson_distribution<long> distribution{lam};
      std::generate(result.fbegin(), result.fend(),
                    [&]() { return distribution(details::generator); });
      return result;
    }

    auto poisson(double lam, long size)
        -> decltype(poisson(lam, types::array<long, 1>{{size}}))
    {
      return poisson(lam, types::array<long, 1>{{size}});
    }

    double poisson(double lam, types::none_type d)
    {
      return std::poisson_distribution<long>{lam}(details::generator);
    }

    DEFINE_FUNCTOR(pythonic::numpy::random, poisson);
  }
}
PYTHONIC_NS_END

#endif
