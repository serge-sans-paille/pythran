#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP

#include "pythonic/include/__dispatch__/update.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      ALIAS_DECL(update, pythonic::__dispatch__::update);

      PROXY_DECL(pythonic::builtins::dict, update);
    }
  }
}

#endif
