#ifndef PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    types::list<long> range(long e);

    types::list<long> range(long b, long e, long s = 1);

    PROXY_DECL(pythonic::__builtin__, range);
  }
}

#endif
