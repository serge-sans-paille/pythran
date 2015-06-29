#ifndef PYTHONIC_BUILTIN_CHR_HPP
#define PYTHONIC_BUILTIN_CHR_HPP

#include "pythonic/include/builtins/chr.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T>
    types::str chr(T const &v)
    {
      return {(char)v};
    }

    PROXY_IMPL(pythonic::builtins, chr);
  }
}

#endif
