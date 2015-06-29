#ifndef PYTHONIC_INCLUDE_BUILTIN_OCT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_OCT_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T>
    types::str oct(T const &v);

    PROXY_DECL(pythonic::builtins, oct);
  }
}

#endif
