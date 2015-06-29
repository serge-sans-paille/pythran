#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      // TODO : Add implementation for tuple as first argument.
      bool endswith(types::str const &s, types::str const &suffix,
                    long start = 0, long end = -1);

      PROXY_DECL(pythonic::builtins::str, endswith);
    }
  }
}
#endif
