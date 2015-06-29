#ifndef PYTHONIC_BUILTIN_SET_REMOVE_HPP
#define PYTHONIC_BUILTIN_SET_REMOVE_HPP

#include "pythonic/include/builtins/set/remove.hpp"

#include "pythonic/__dispatch__/remove.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS(remove, pythonic::__dispatch__::remove);

      PROXY_IMPL(pythonic::builtins::set, remove);
    }
  }
}
#endif
