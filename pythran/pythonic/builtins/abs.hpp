#ifndef PYTHONIC_BUILTIN_ABS_HPP
#define PYTHONIC_BUILTIN_ABS_HPP

#include "pythonic/include/builtins/abs.hpp"

#include "pythonic/numpy/abs.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    ALIAS(abs, numpy::proxy::abs{});
    PROXY_IMPL(pythonic::builtins, abs);
  }
}

#endif
