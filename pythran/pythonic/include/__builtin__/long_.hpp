#ifndef PYTHONIC_INCLUDE_BUILTIN_LONG_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LONG_HPP

#include "pythonic/include/types/long.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    pythran_long_t long_(T &&t);

    pythran_long_t long_();

    PROXY_DECL(pythonic::__builtin__, long_);
  }
}

#endif
