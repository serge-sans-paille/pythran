#ifndef PYTHONIC_BUILTIN_FLOAT_HPP
#define PYTHONIC_BUILTIN_FLOAT_HPP

#include "pythonic/include/__builtin__/float_.hpp"

#include "pythonic/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {

    namespace functor
    {
      template <class T>
      float_::type float_::operator()(T &&t)
      {
        return t;
      }

      float_::type float_::operator()()
      {
        return 0.;
      }

#ifdef USE_GMP
      template <class T, class U>
      float_::type float_::operator()(__gmp_expr<T, U> const &a)
      {
        return mpz_get_d(a.get_mpz_t());
      }
      template <class T, class U>
      float_::type float_::operator()(__gmp_expr<T, U> &a)
      {
        return mpz_get_d(a.get_mpz_t());
      }
#endif
    }
  }
}

#endif
