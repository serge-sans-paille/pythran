#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_COPY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS_DECL(copy, pythonic::__dispatch__::copy);

      PROXY_DECL(pythonic::builtins::set, copy);
    }
  }
}
#endif
