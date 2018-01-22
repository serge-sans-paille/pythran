#ifndef PYTHONIC_BUILTIN_FLOAT_HPP
#define PYTHONIC_BUILTIN_FLOAT_HPP

#include "pythonic/include/__builtin__/float_.hpp"

#include "pythonic/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {
    template <class T>
    float_::type float_::operator()(T &&t) const
    {
      return t;
    }

    float_::type float_::operator()() const
    {
      return 0.;
    }

#ifdef USE_GMP
    template <class T, class U>
    float_::type float_::operator()(__gmp_expr<T, U> const &a) const
    {
      return mpz_get_d(a.get_mpz_t());
    }
    template <class T, class U>
    float_::type float_::operator()(__gmp_expr<T, U> &a) const
    {
      return mpz_get_d(a.get_mpz_t());
    }
#endif
  }
}
PYTHONIC_NS_END

#endif
