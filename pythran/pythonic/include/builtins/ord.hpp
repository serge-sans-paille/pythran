#ifndef PYTHONIC_INCLUDE_BUILTIN_ORD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ORD_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    long ord(types::str const &v);

    long ord(char v);

    PROXY_DECL(pythonic::builtins, ord);
  }
}

#endif
