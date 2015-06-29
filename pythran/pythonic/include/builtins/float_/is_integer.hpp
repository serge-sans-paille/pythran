#ifndef PYTHONIC_INCLUDE_BUILTIN_FLOAT_ISINTEGER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FLOAT_ISINTEGER_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace float_
    {

      bool is_integer(double d);

      PROXY_DECL(pythonic::builtins::float_, is_integer);
    }
  }
}

#endif
