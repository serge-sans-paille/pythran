#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_FIND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_FIND_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      long find(types::str const &s, types::str const &value, long start,
                long end);

      long find(types::str const &s, types::str const &value, long start);

      long find(types::str const &s, types::str const &value);

      PROXY_DECL(pythonic::builtins::str, find);
    }
  }
}
#endif
