#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_SUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_SUM_HPP

#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {
    USING_FUNCTOR(sum, numpy::functor::sum);
  }
} // namespace numpy
PYTHONIC_NS_END

#endif
