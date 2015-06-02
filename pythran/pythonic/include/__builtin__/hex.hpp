#ifndef PYTHONIC_INCLUDE_BUILTIN_HEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_HEX_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    types::str hex(T const &v);

    PROXY_DECL(pythonic::__builtin__, hex);
  }
}

#endif
