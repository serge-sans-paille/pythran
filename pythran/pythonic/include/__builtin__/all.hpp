#ifndef PYTHONIC_INCLUDE_BUILTIN_ALL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ALL_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class Iterable>
    bool all(Iterable &&s);

    PROXY_DECL(pythonic::__builtin__, all);
  }
}

#endif
