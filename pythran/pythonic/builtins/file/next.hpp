#ifndef PYTHONIC_BUILTIN_FILE_NEXT_HPP
#define PYTHONIC_BUILTIN_FILE_NEXT_HPP

#include "pythonic/include/builtins/file/next.hpp"

#include "pythonic/__dispatch__/next.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      ALIAS(next, pythonic::__dispatch__::next);

      PROXY_IMPL(pythonic::builtins::file, next);
    }
  }
}
#endif
