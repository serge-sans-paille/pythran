#ifndef PYTHONIC_BUILTIN_ANY_HPP
#define PYTHONIC_BUILTIN_ANY_HPP

#include "pythonic/include/builtins/any.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class Iterable>
    bool any(Iterable &&s)
    {
      auto iend = s.end();
      for (auto iter = s.begin(); iter != iend; ++iter)
        if (*iter)
          return true;
      return false;
    }

    PROXY_IMPL(pythonic::builtins, any);
  }
}

#endif
