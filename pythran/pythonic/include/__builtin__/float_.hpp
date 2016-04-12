#ifndef PYTHONIC_INCLUDE_BUILTIN_FLOAT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FLOAT_HPP

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
      struct float_ {
        using callable = void;
        using type = double;

        template <class T>
        type operator()(T &&t);

        type operator()();

#ifdef USE_GMP
        template <class T, class U>
        type operator()(__gmp_expr<T, U> const &a);
        template <class T, class U>
        type operator()(__gmp_expr<T, U> &a);
#endif
      };
    }
  }
}

#endif
