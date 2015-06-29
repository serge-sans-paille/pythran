#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_REMOVE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_REMOVE_HPP

#include "pythonic/include/__dispatch__/remove.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS_DECL(remove, pythonic::__dispatch__::remove);

      PROXY_DECL(pythonic::builtins::set, remove);
    }
  }
}
#endif
