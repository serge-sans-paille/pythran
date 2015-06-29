#ifndef PYTHONIC_BUILTIN_DICT_POP_HPP
#define PYTHONIC_BUILTIN_DICT_POP_HPP

#include "pythonic/include/builtins/dict/pop.hpp"

#include "pythonic/__dispatch__/pop.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS(pop, pythonic::__dispatch__::pop);

      PROXY_IMPL(pythonic::builtins::dict, pop);
    }
  }
}

#endif
