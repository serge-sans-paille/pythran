#ifndef PYTHONIC_INCLUDE_BUILTIN_CMP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_CMP_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T0, class T1>
    long cmp(T0 const &v0, T1 const &v1);

    PROXY_DECL(pythonic::builtins, cmp);
  }
}

#endif
