//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief fast_sincos generic tag

     Represents the fast_sincos function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_sincos_ : ext::elementwise_<fast_sincos_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_sincos_> parent;
    };
  }
  /*!
    Computes simultaneously sine and cosine  in the interval
    \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    tie(s, c) = fast_sincos(x);
    @endcode

    is similar to:

    @code
    T0 c = fast_cos(x);
    T0 s = fast_sin(x);
    @endcode

    @see @funcref{sine}, @funcref{fast_sin}, @funcref{sincos}, @funcref{fast_cos}
    @param a0 input

    @return a pair of value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincos_, fast_sincos, 1)
  /*!
    Computes simultaneously sine and cosine  in the interval
    \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    s = fast_sincos(x, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cos(x);
    T0 s = fast_sin(x);
    @endcode

    @see @funcref{sine}, @funcref{fast_sin}, @funcref{sincos}, @funcref{fast_cos}
    @param a0 input
    @param a1 L-Value that will receive the cosine of a0
    @return the sine of a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&),2)
  /*!
    Computes simultaneously sine and cosine  in the interval
    \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    fast_sincos(x, s, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cos(x);
    T0 s = fast_sin(x);
    @endcode

    @see @funcref{sine}, @funcref{fast_sin}, @funcref{sincos}, @funcref{fast_cos}
    @param a0 Value to decompose
    @param a1 L-Value that will receive the sine of @c a0
    @param a2 L-Value that will receive the cosine of @c a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&)(A2&),3)
}

#endif


