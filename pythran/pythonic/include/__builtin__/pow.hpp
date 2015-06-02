#ifndef PYTHONIC_INCLUDE_BUILTIN_POW_HPP
#define PYTHONIC_INCLUDE_BUILTIN_POW_HPP

#include "pythonic/include/numpy/power.hpp"
#include "pythonic/include/utils/proxy.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {

    ALIAS_DECL(pow, numpy::proxy::power{});

#ifdef USE_GMP
    template <class T, class U>
    pythran_long_t pow(__gmp_expr<T, U> const &a, long b);
#endif

    PROXY_DECL(pythonic::__builtin__, pow);
  }
}

#endif
