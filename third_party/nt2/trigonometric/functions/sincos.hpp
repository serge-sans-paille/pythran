//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINCOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINCOS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sincos function
    struct sincos_ : ext::elementwise_<sincos_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sincos_> parent;
    };
  }
  /*!
    Computes simultaneously the sine and cosine of the input

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 s, c;
    tie(s, c) = sincos(x);
    @endcode

    is similar to:

    @code
    T0 s =  sin(x);
    T0 c =  cos(x);
    @endcode

    @see @funcref{fast_sincos}, @funcref{sincosine}, @funcref{sincosd}, @funcref{sincospi}
    @param a0 angle in radian

    @return A Fusion Sequence containing the sin and cos of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sincos_, sincos, 1)

  /*!
    Computes simultaneously the sine and cosine of the input

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 s, c;
    s = sincos(x, c);
    @endcode

    is similar to:

    @code
    T0 s =  sin(x);
    T0 c =  cos(x);
    @endcode

    @param a0 angle in radian
    @param a1 L-Value that will receive the sin of @c a0

    @return the sin of a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincos_, sincos,(A0 const&)(A1&),2)

  /*!
    Computes the sine and cosine of the input

    For every parameters of floating type T0:

    @par Semantic:

    @code
    T0 s, c;
    sincos(x, s, c);
    @endcode

    is similar to:

    @code
    T0 s =  sin(x);
    T0 c =  cos(x);
    @endcode

    @param a0 angle in radian
    @param a1 L-Value that will receive the sin of @c a0
    @param a2 L-Value that will receive the cos of @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincos_, sincos,(A0 const&)(A1&)(A2&),3)

    }

#endif


