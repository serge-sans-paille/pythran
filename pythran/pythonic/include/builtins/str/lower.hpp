#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_LOWER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_LOWER_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str lower(types::str const &s);

      PROXY_DECL(pythonic::builtins::str, lower);
    }
  }
}
#endif
