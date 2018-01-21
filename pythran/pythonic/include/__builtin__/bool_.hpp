#ifndef PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP

#include "pythonic/include/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {

    struct bool_ {
      using callable = void;
      using type = bool;

      bool operator()() const;

      template <class T>
      bool operator()(T &&val) const;

#ifdef USE_GMP
      template <class T, class U>
      bool operator()(__gmp_expr<T, U> const &a) const;

      template <class T, class U>
      bool operator()(__gmp_expr<T, U> &&a) const;
#endif
    };
  }
}
PYTHONIC_NS_END

#endif
