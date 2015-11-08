//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_POW2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_POW2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief pow2 generic tag

     Represents the pow2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct pow2_ : ext::elementwise_<pow2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pow2_> parent;
    };
  }
  /*!
     Returns  base 2 power of input (the result is undefined on overflow and
     the functor asserts for invalid input)

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = pow2(x);
    @endcode

    is similar to:

    @code
    T0 r = exp2(trunc(x));
    @endcode

    @see @funcref{exp2}, @funcref{trunc}
    @param a0

    @return a value of the same type as the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2_, pow2, 1)
  /*!
    Returns \f$ x 2^y\f$.  (the result is undefined on overflow and
    the functor asserts for invalid second parameter )

    @par Semantic:

    For every parameters of floating type T0

    @code
    T0 r = pow2(x, y);
    @endcode

    is similar to:

    @code
    T0 r = x*exp2(trunc(y));
    @endcode

    @see @funcref{exp2}, @funcref{trunc}, @funcref{ldexp}
    @param a0
    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2_, pow2, 2)
}

#endif
