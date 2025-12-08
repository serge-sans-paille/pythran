#ifndef PYTHONIC_INCLUDE_NUMPY_CONCAT_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONCAT_HPP

#include "pythonic/include/numpy/concatenate.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  USING_FUNCTOR(concat, numpy::functor::concatenate);
}
PYTHONIC_NS_END

#endif
