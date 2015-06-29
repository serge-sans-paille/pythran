#ifndef PYTHONIC_INCLUDE_BUILTIN_ALL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ALL_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    template <class Iterable>
    bool all(Iterable &&s);

    PROXY_DECL(pythonic::builtins, all);
  }
}

#endif
