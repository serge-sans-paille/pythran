#ifndef PYTHONIC_INCLUDE_BUILTIN_ROUND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ROUND_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {
    template <class T>
    double round(T const &v, size_t n);

    template <class T>
    double round(T const &v);

    PROXY_DECL(pythonic::builtins, round);
  }
}

#endif
