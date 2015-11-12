//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_sincospi generic tag

     Represents the fast_sincospi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_sincospi_ : ext::elementwise_<fast_sincospi_> { typedef ext::elementwise_<fast_sincospi_> parent; };
  }
  /*!
    Computes simultaneously sine and cosine from angle in \f$\pi\f$ multiples
    in the interval \f$[-1/4,1/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    tie(s, c)= fast_sincospi(a0);
    @endcode

    is similar to:

    @code
    T0 c = fast_cospi(x);
    T0 s = fast_sinpi(x);
    @endcode

    @see @funcref{fast_sinpi}, @funcref{sincospi}, @funcref{fast_cospi}
    @param a0 input

    @return a pair of value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincospi_, fast_sincospi, 1)
  /*!
    Computes simultaneously sine and cosine from angle in \f$\pi\f$ multiples
    in the interval \f$[-1/4,1/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    s = fast_sincospi(x, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cospi(x);
    T0 s = fast_sinpi(x);
    @endcode

    @see @funcref{fast_sinpi}, @funcref{sincospi}, @funcref{fast_cospi}
    @param a0 input in pi multiples
    @param a1 L-Value that will receive the cosine of a0
    @return the sine of a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&),2)
  /*!
    Computes simultaneously sine and cosine from angle in \f$\pi\f$ multiples
    in the interval \f$[-1/4,1/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    fast_sincospi(x, s, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cospi(x);
    T0 s = fast_sinpi(x);
    @endcode

    @see @funcref{fast_sinpi}, @funcref{sincospi}, @funcref{fast_cospi}
    @param a0 input in pi multiples
    @param a1 L-Value that will receive the sine of a0
    @param a2 L-Value that will receive the cosine of a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&)(A2&),3)
}

#endif


