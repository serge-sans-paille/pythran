#ifndef PYTHONIC_INCLUDE_BUILTIN_ANY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ANY_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class Iterable>
    bool any(Iterable &&s);

    PROXY_DECL(pythonic::builtins, any);
  }
}

#endif
