#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_POISSON_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_POISSON_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {
    template <size_t N>
    types::ndarray<double, N> poisson(double lam,
                                      types::array<long, N> const &shape);

    auto poisson(double lam, long size)
        -> decltype(poisson(lam, types::array<long, 1>{{size}}));

    double poisson(double lam = 1.0, types::none_type size = {});

    DECLARE_FUNCTOR(pythonic::numpy::random, poisson);
  }
}
PYTHONIC_NS_END

#endif
