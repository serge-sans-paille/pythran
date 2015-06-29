#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_COPY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS_DECL(copy, pythonic::__dispatch__::copy);

      PROXY_DECL(pythonic::builtins::dict, copy);
    }
  }
}

#endif
