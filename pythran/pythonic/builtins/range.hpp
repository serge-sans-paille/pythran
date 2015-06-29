#ifndef PYTHONIC_BUILTIN_RANGE_HPP
#define PYTHONIC_BUILTIN_RANGE_HPP

#include "pythonic/include/builtins/range.hpp"

#include "pythonic/builtins/xrange.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic
{

  namespace builtins
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

    PROXY_IMPL(pythonic::builtins, range);
  }
}

#endif
