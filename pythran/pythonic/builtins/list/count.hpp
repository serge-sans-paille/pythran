#ifndef PYTHONIC_BUILTIN_LIST_COUNT_HPP
#define PYTHONIC_BUILTIN_LIST_COUNT_HPP

#include "pythonic/include/builtins/list/count.hpp"

#include "pythonic/__dispatch__/count.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      ALIAS(count, pythonic::__dispatch__::count);

      PROXY_IMPL(pythonic::builtins::list, count);
    }
  }
}

#endif
