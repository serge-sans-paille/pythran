//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ACOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ACOS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief acos generic tag

     Represents the acos function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acos_ : ext::elementwise_<acos_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acos_> parent;
    };
  }
  /*!
    inverse cosine in radian.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acos(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, \pi[\f$ such that <tt>cos(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see @funcref{acosd}, @funcref{acospi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acos_, acos, 1)
}

#endif

