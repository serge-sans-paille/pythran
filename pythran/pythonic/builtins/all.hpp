#ifndef PYTHONIC_BUILTIN_ALL_HPP
#define PYTHONIC_BUILTIN_ALL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/builtins/all.hpp"

namespace pythonic
{

  namespace builtins
  {

    template <class Iterable>
    bool all(Iterable &&s)
    {
      auto iend = s.end();
      for (auto iter = s.begin(); iter != iend; ++iter)
        if (not*iter)
          return false;
      return true;
    }
    PROXY_IMPL(pythonic::builtins, all);
  }
}

#endif
