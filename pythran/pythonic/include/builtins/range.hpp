#ifndef PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_RANGE_HPP

#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    types::list<long> range(long e);

    types::list<long> range(long b, long e, long s = 1);

    PROXY_DECL(pythonic::builtins, range);
  }
}

#endif
