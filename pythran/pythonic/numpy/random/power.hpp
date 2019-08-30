#ifndef PYTHONIC_NUMPY_RANDOM_POWER_HPP
#define PYTHONIC_NUMPY_RANDOM_POWER_HPP

#include "pythonic/include/numpy/random/power.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"
#include <math.h>

#include <random>
#include <algorithm>

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {

    template <class pS>
    types::ndarray<double, pS> power(double a, pS const &shape)
    {
      types::ndarray<double, pS> result{shape, types::none_type()};
      std::generate(result.fbegin(), result.fend(), [&]() { return power(a); });

      return result;
    }

    auto power(double a, long size)
        -> decltype(power(a, types::array<long, 1>{{size}}))
    {
      return power(a, types::array<long, 1>{{size}});
    }

    double power(double a, types::none_type d)
    {
      return pow(
          -expm1(-std::exponential_distribution<double>{}(details::generator)),
          1. / a);
    }
  }
}
PYTHONIC_NS_END

#endif
