#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_PROD_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_PROD_HPP

#include "pythonic/include/numpy/prod.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {
    USING_FUNCTOR(prod, numpy::functor::prod);
  }
} // namespace numpy
PYTHONIC_NS_END

#endif
