#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_NEGATIVE_BINOMIAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_NEGATIVE_BINOMIAL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {
    template <class pS>
    types::ndarray<double, pS> negative_binomial(double n, double p,
                                                 pS const &shape);

    auto negative_binomial(double n, double p, long size)
        -> decltype(negative_binomial(n, p, types::array<long, 1>{{size}}));

    double negative_binomial(double n, double p, types::none_type size = {});

    DEFINE_FUNCTOR(pythonic::numpy::random, negative_binomial);
  }
}
PYTHONIC_NS_END

#endif