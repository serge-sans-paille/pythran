#ifndef PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP

#include "pythonic/include/utils/functor.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace pythonic
{

  namespace __builtin__
  {

    namespace functor
    {

      struct bool_ {
        using callable = void;
        using type = bool;

        bool operator()();

        template <class T>
        bool operator()(T &&val);

#ifdef USE_GMP
        template <class T, class U>
        bool operator()(__gmp_expr<T, U> const &a);

        template <class T, class U>
        bool operator()(__gmp_expr<T, U> &&a);
#endif
      };
    }
  }
}

#endif
