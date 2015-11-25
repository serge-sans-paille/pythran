#ifndef PYTHONIC_INCLUDE_BUILTIN_POW_HPP
#define PYTHONIC_INCLUDE_BUILTIN_POW_HPP

#include "pythonic/include/numpy/power.hpp"
#include "pythonic/include/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {
    template <class... Types>
    auto pow(Types &&... args)
        -> decltype(numpy::functor::power{}(std::forward<Types>(args)...));
#ifdef USE_GMP
    template <class T, class U>
    pythran_long_t pow(__gmp_expr<T, U> const &a, long b);
#endif
    DECLARE_FUNCTOR(pythonic::__builtin__, pow);
  }
}

#endif
