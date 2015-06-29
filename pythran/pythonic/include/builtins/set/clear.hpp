#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_CLEAR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_CLEAR_HPP

#include "pythonic/include/__dispatch__/clear.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS_DECL(clear, pythonic::__dispatch__::clear);

      PROXY_DECL(pythonic::builtins::set, clear);
    }
  }
}
#endif
