#ifndef PYTHONIC_INCLUDE_FUNCTOOLS_REDUCE_HPP
#define PYTHONIC_INCLUDE_FUNCTOOLS_REDUCE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/reduce.hpp"

PYTHONIC_NS_BEGIN

namespace functools
{
  USING_FUNCTOR(reduce, __builtin__::functor::reduce);
}
PYTHONIC_NS_END

#endif
