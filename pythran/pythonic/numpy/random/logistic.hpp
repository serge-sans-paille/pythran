#ifndef PYTHONIC_NUMPY_RANDOM_LOGISTIC_HPP
#define PYTHONIC_NUMPY_RANDOM_LOGISTIC_HPP

#include "pythonic/include/numpy/random/logistic.hpp"
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
    types::ndarray<double, pS> logistic(double loc, double scale,
                                        pS const &shape)
    {
      types::ndarray<double, pS> result{shape, types::none_type()};
      std::generate(result.fbegin(), result.fend(),
                    [&]() { return logistic(loc, scale); });
      return result;
    }

    auto logistic(double loc, double scale, long size)
        -> decltype(logistic(loc, scale, types::array<long, 1>{{size}}))
    {
      return logistic(loc, scale, types::array<long, 1>{{size}});
    }

    double logistic(double loc, double scale, types::none_type d)
    {
      double U =
          std::uniform_real_distribution<double>{0., 1.}(details::generator);
      if (U > 0.0) {
        return loc + scale * xsimd::log(U / (1 - U));
      }
      return logistic(loc, scale);
    }
  }
}
PYTHONIC_NS_END

#endif
