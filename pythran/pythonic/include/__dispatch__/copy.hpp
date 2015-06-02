#ifndef PYTHONIC_INCLUDE_DISPATCH_COPY_HPP
#define PYTHONIC_INCLUDE_DISPATCH_COPY_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any>
    auto copy(Any const &any) -> decltype(any.copy());

    PROXY_DECL(pythonic::__dispatch__, copy);
  }
}

#endif
