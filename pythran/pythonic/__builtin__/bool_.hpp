#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/include/__builtin__/bool_.hpp"

#include "pythonic/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {
    namespace functor
    {

      template <class T>
      bool bool_::operator()(T &&val)
      {
        return (bool)val;
      }

      bool bool_::operator()()
      {
        return false;
      }

#ifdef USE_GMP
      template <class T, class U>
      bool bool_::operator()(__gmp_expr<T, U> const &a)
      {
        return a != 0;
      }
      template <class T, class U>
      bool bool_::operator()(__gmp_expr<T, U> &&a)
      {
        return a != 0;
      }
#endif
    }
  }
}

#endif
