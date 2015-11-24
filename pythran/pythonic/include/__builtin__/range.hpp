#ifndef PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    types::list<long> range(long e);

    types::list<long> range(long b, long e, long s = 1);

    DECLARE_FUNCTOR(pythonic::__builtin__, range);
  }
}

#endif
