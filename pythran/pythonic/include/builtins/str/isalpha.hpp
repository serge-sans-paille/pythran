#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      bool isalpha(types::str const &s);

      PROXY_DECL(pythonic::builtins::str, isalpha);
    }
  }
}
#endif
