#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_WEIBULL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_WEIBULL_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {
    template <class pS>
    types::ndarray<double, pS> weibull(float a, pS const &shape);

    auto weibull(float a, long size)
        -> decltype(weibull(a, types::array<long, 1>{{size}}));

    double weibull(float a, types::none_type size = {});

    DEFINE_FUNCTOR(pythonic::numpy::random, weibull);
  }
}
PYTHONIC_NS_END

#endif
