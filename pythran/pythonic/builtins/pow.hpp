#ifndef PYTHONIC_BUILTIN_POW_HPP
#define PYTHONIC_BUILTIN_POW_HPP

#include "pythonic/include/builtins/pow.hpp"

#include "pythonic/numpy/power.hpp"
#include "pythonic/utils/proxy.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

namespace pythonic
{

  namespace builtins
  {

    ALIAS(pow, numpy::proxy::power{});

#ifdef USE_GMP
    template <class T, class U>
    pythran_long_t pow(__gmp_expr<T, U> const &a, long b)
    {
      mpz_class rop;
      mpz_pow_ui(rop.get_mpz_t(), a.get_mpz_t(), b);
      return rop;
    }
#endif

    PROXY_IMPL(pythonic::builtins, pow);
  }
}

#endif
