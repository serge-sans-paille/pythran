#ifndef PYTHONIC_NUMPY_RANDOM_NORMAL_HPP
#define PYTHONIC_NUMPY_RANDOM_NORMAL_HPP

#include "pythonic/include/numpy/random/normal.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"

#include <random>
#include <algorithm>

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {

    template <class pS>
    types::ndarray<double, pS> normal(double loc, double scale, pS const &shape)
    {
      types::ndarray<double, pS> result{shape, types::none_type()};
      std::normal_distribution<double> distribution{loc, scale};
      std::generate(result.fbegin(), result.fend(),
                    [&]() { return distribution(details::generator); });
      return result;
    }

    auto normal(double loc, double scale, long size)
        -> decltype(normal(loc, scale, types::array<long, 1>{{size}}))
    {
      return normal(loc, scale, types::array<long, 1>{{size}});
    }

    double normal(double loc, double scale, types::none_type d)
    {
      return std::normal_distribution<double>{loc, scale}(details::generator);
    }

    DEFINE_FUNCTOR(pythonic::numpy::random, normal);
  }
}
PYTHONIC_NS_END

#endif
