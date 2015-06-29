#ifndef PYTHONIC_BUILTIN_SET_COPY_HPP
#define PYTHONIC_BUILTIN_SET_COPY_HPP

#include "pythonic/include/builtins/set/copy.hpp"

#include "pythonic/__dispatch__/copy.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS(copy, pythonic::__dispatch__::copy);

      PROXY_IMPL(pythonic::builtins::set, copy);
    }
  }
}
#endif
