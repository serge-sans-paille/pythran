#ifndef PYTHONIC_BUILTIN_RANGE_HPP
#define PYTHONIC_BUILTIN_RANGE_HPP

#include "pythonic/include/__builtin__/range.hpp"

#include "pythonic/__builtin__/xrange.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    types::list<long> range(long e)
    {
      xrange xr(e);
      return {xr.begin(), xr.end()};
    }

    types::list<long> range(long b, long e, long s)
    {
      xrange xr(b, e, s);
      return {xr.begin(), xr.end()};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, range);
  }
}

#endif
