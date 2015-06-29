#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_UPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_UPDATE_HPP

#include "pythonic/include/__dispatch__/update.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS_DECL(update, pythonic::__dispatch__::update);

      PROXY_DECL(pythonic::builtins::set, update);
    }
  }
}
#endif
