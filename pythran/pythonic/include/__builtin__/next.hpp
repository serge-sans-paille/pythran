#ifndef PYTHONIC_INCLUDE_BUILTIN_NEXT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_NEXT_HPP

#include "pythonic/include/utils/proxy.hpp"

#include <utility>

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    auto next(T &&y) -> decltype(*y);

    PROXY_DECL(pythonic::__builtin__, next);
  }
}

#endif
