#ifndef PYTHONIC_BUILTIN_LIST_REMOVE_HPP
#define PYTHONIC_BUILTIN_LIST_REMOVE_HPP

#include "pythonic/include/builtins/list/remove.hpp"

#include "pythonic/__dispatch__/remove.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      ALIAS(remove, pythonic::__dispatch__::remove);

      PROXY_IMPL(pythonic::builtins::list, remove);
    }
  }
}
#endif
