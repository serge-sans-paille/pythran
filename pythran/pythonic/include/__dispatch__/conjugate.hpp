#ifndef PYTHONIC_INCLUDE_DISPATCH_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_DISPATCH_CONJUGATE_HPP

#include "pythonic/include/numpy/conjugate.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any>
    auto conjugate(Any const &any) -> decltype(numpy::proxy::conjugate{}(any));

    PROXY_DECL(pythonic::__dispatch__, conjugate);
  }
}

#endif
