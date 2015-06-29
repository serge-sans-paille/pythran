#ifndef PYTHONIC_BUILTIN_DICT_COPY_HPP
#define PYTHONIC_BUILTIN_DICT_COPY_HPP

#include "pythonic/include/builtins/dict/copy.hpp"

#include "pythonic/__dispatch__/copy.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS(copy, pythonic::__dispatch__::copy);

      PROXY_IMPL(pythonic::builtins::dict, copy);
    }
  }
}

#endif
