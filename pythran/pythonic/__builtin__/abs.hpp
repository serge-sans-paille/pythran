#ifndef PYTHONIC_BUILTIN_ABS_HPP
#define PYTHONIC_BUILTIN_ABS_HPP

#include "pythonic/include/__builtin__/abs.hpp"

#include "pythonic/numpy/abs.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    ALIAS(abs, numpy::proxy::abs{});
    PROXY_IMPL(pythonic::__builtin__, abs);
  }
}

#endif
