#ifndef PYTHONIC_BUILTIN_DICT_CLEAR_HPP
#define PYTHONIC_BUILTIN_DICT_CLEAR_HPP

#include "pythonic/include/builtins/dict/clear.hpp"

#include "pythonic/__dispatch__/clear.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS(clear, pythonic::__dispatch__::clear);

      PROXY_IMPL(pythonic::builtins::dict, clear);
    }
  }
}

#endif
