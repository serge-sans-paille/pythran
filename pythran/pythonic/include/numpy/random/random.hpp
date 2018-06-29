#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDOM_HPP

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
    types::ndarray<double, pS> random(pS const &shape);

    auto random(long size) -> decltype(random(types::array<long, 1>{{size}}));

    double random(types::none_type d = types::none_type());

    DECLARE_FUNCTOR(pythonic::numpy::random, random);
  }
}
PYTHONIC_NS_END

#endif
