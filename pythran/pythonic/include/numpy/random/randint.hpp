#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDINT_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_RANDINT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace random
  {
    template <class pS>
    types::ndarray<long, pS> randint(long min, long max, pS const &shape);

    long randint(long min, long max);

    long randint(long max);

    auto randint(long min, long max, long size)
        -> decltype(randint(min, max, types::array<long, 1>{{size}}));

    DEFINE_FUNCTOR(pythonic::numpy::random, randint);
  }
}
PYTHONIC_NS_END

#endif
