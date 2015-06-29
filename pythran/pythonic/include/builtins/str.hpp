#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace anonymous
    {
      template <class T>
      types::str str(T &&t);

      inline types::str str(long value);
      inline types::str str(double l);
    }

    PROXY_DECL(pythonic::builtins::anonymous, str);
  }
}

#endif
