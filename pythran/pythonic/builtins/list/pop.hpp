#ifndef PYTHONIC_BUILTIN_LIST_POP_HPP
#define PYTHONIC_BUILTIN_LIST_POP_HPP

#include "pythonic/include/builtins/list/pop.hpp"

#include "pythonic/__dispatch__/pop.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      ALIAS(pop, pythonic::__dispatch__::pop);

      PROXY_IMPL(pythonic::builtins::list, pop);
    }
  }
}
#endif
