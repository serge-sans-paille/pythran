#ifndef PYTHONIC_INCLUDE_NUMPY_RANDOM_CHISQUARE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANDOM_CHISQUARE_HPP

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
    types::ndarray<double, pS> chisquare(float df, pS const &shape);

    auto chisquare(float df, long size)
        -> decltype(chisquare(df, types::array<long, 1>{{size}}));

    double chisquare(float df, types::none_type size = {});

    DEFINE_FUNCTOR(pythonic::numpy::random, chisquare);
  }
}
PYTHONIC_NS_END

#endif
