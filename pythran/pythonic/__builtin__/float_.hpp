#ifndef PYTHONIC_BUILTIN_FLOAT_HPP
#define PYTHONIC_BUILTIN_FLOAT_HPP

#include "pythonic/include/__builtin__/float_.hpp"

#include "pythonic/utils/proxy.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {

    namespace anonymous
    {
      template <class T>
      double float_(T &&t)
      {
        return t;
      }

      double float_()
      {
        return 0.;
      }

#ifdef USE_GMP
      template <class T, class U>
      double float_(__gmp_expr<T, U> const &a)
      {
        return mpz_get_d(a.get_mpz_t());
      }
#endif
    }

    PROXY_IMPL(pythonic::__builtin__::anonymous, float_);
  }
}

#endif
