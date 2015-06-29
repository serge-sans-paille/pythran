#ifndef PYTHONIC_BUILTIN_CMP_HPP
#define PYTHONIC_BUILTIN_CMP_HPP

#include "pythonic/include/builtins/cmp.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T0, class T1>
    long cmp(T0 const &v0, T1 const &v1)
    {
      return v0 == v1 ? 0 : (v0 < v1 ? -1 : 1);
    }

    PROXY_IMPL(pythonic::builtins, cmp);
  }
}

#endif
