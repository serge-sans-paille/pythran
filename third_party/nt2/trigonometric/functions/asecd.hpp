//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ASECD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ASECD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief asecd generic tag

     Represents the asecd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct asecd_ : ext::elementwise_<asecd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<asecd_> parent;
    };
  }
  /*!
     inverse secant in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = asecd(a0);
    @endcode

    is similar to:

    @code
    T0 r =  acosd(rec(a0));;
    @endcode

    @see @funcref{asec}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asecd_, asecd, 1)
}

#endif


