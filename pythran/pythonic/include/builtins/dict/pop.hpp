#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_POP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_POP_HPP

#include "pythonic/include/__dispatch__/pop.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS_DECL(pop, pythonic::__dispatch__::pop);

      PROXY_DECL(pythonic::builtins::dict, pop);
    }
  }
}

#endif
