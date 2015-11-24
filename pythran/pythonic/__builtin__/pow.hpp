#ifndef PYTHONIC_BUILTIN_POW_HPP
#define PYTHONIC_BUILTIN_POW_HPP

#include "pythonic/include/__builtin__/pow.hpp"

#include "pythonic/numpy/power.hpp"
#include "pythonic/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {
    template <class... Types>
    auto pow(Types &&... args)
        -> decltype(numpy::functor::power{}(std::forward<Types>(args)...))
    {
      return numpy::functor::power{}(std::forward<Types>(args)...);
    }
#ifdef USE_GMP
    template <class T, class U>
    pythran_long_t pow(__gmp_expr<T, U> const &a, long b)
    {
      mpz_class rop;
      mpz_pow_ui(rop.get_mpz_t(), a.get_mpz_t(), b);
      return rop;
    }
#endif
    DEFINE_FUNCTOR(pythonic::__builtin__, pow);
  }
}

#endif
