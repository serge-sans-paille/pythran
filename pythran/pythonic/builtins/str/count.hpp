#ifndef PYTHONIC_BUILTIN_STR_COUNT_HPP
#define PYTHONIC_BUILTIN_STR_COUNT_HPP

#include "pythonic/include/builtins/str/count.hpp"

#include "pythonic/__dispatch__/count.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      ALIAS(count, pythonic::__dispatch__::count);

      PROXY_IMPL(pythonic::builtins::str, count);
    }
  }
}
#endif
