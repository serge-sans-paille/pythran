#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_COUNT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_COUNT_HPP

#include "pythonic/include/__dispatch__/count.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      ALIAS_DECL(count, pythonic::__dispatch__::count);

      PROXY_DECL(pythonic::builtins::list, count);
    }
  }
}

#endif
