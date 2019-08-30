#ifndef PYTHONIC_NUMPY_RANDOM_NEGATIVE_BINOMIAL_HPP
#define PYTHONIC_NUMPY_RANDOM_NEGATIVE_BINOMIAL_HPP

#include "pythonic/include/numpy/random/negative_binomial.hpp"
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
    types::ndarray<double, pS> negative_binomial(double n, double p,
                                                 pS const &shape)
    {
      types::ndarray<double, pS> result{shape, types::none_type()};
      std::gamma_distribution<double> distribution_gamma{n, (1 - p) / p};
      std::generate(result.fbegin(), result.fend(), [&]() {
        return std::poisson_distribution<long>{
            (distribution_gamma(details::generator))}(details::generator);
      });
      return result;
    }

    auto negative_binomial(double n, double p, long size)
        -> decltype(negative_binomial(n, p, types::array<long, 1>{{size}}))
    {
      return negative_binomial(n, p, types::array<long, 1>{{size}});
    }

    double negative_binomial(double n, double p, types::none_type d)
    {
      std::gamma_distribution<double> distribution_gamma{n, (1 - p) / p};
      return std::poisson_distribution<long>{
          (distribution_gamma(details::generator))}(details::generator);
    }
  }
}
PYTHONIC_NS_END

#endif
