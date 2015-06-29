#ifndef PYTHONIC_INCLUDE_BUILTIN_LONG_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LONG_HPP

#include "pythonic/include/types/long.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    template <class T>
    pythran_long_t long_(T &&t);

    pythran_long_t long_();

    PROXY_DECL(pythonic::builtins, long_);
  }
}

#endif
