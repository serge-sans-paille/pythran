#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str rstrip(types::str const &self, types::str const &to_del = " ");

      PROXY_DECL(pythonic::__builtin__::str, rstrip);
    }
  }
}
#endif
