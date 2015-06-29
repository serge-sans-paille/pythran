#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISDIGIT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISDIGIT_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      bool isdigit(types::str const &s);

      PROXY_DECL(pythonic::builtins::str, isdigit);
    }
  }
}
#endif
