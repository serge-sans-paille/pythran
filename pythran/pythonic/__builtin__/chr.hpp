#ifndef PYTHONIC_BUILTIN_CHR_HPP
#define PYTHONIC_BUILTIN_CHR_HPP

#include "pythonic/include/__builtin__/chr.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class T>
    types::str chr(T const &v)
    {
      return {(char)v};
    }

    PROXY_IMPL(pythonic::__builtin__, chr);
  }
}

#endif
