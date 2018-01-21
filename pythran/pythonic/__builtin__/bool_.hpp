#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/include/__builtin__/bool_.hpp"

#include "pythonic/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  namespace functor
  {

    template <class T>
    bool bool_::operator()(T &&val) const
    {
      return (bool)val;
    }

    bool bool_::operator()() const
    {
      return false;
    }

#ifdef USE_GMP
    template <class T, class U>
    bool bool_::operator()(__gmp_expr<T, U> const &a) const
    {
      return a != 0;
    }
    template <class T, class U>
    bool bool_::operator()(__gmp_expr<T, U> &&a) const
    {
      return a != 0;
    }
#endif
  }
}
PYTHONIC_NS_END

#endif
