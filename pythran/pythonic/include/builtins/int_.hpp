#ifndef PYTHONIC_INCLUDE_BUILTIN_INT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_INT_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    template <class T>
    long int_(T &&t);

    long int_(char t);

    long int_();

    PROXY_DECL(pythonic::builtins, int_);
  }
}

#endif
