#ifndef PYTHONIC_INCLUDE_BUILTIN_CHR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_CHR_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T>
    types::str chr(T const &v);

    PROXY_DECL(pythonic::builtins, chr);
  }
}

#endif
