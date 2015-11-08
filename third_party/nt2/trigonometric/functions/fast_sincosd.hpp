//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_sincosd generic tag

     Represents the fast_sincosd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_sincosd_ : ext::elementwise_<fast_sincosd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_sincosd_> parent;
    };
  }
  /*!
    Computes simultaneously sine and cosine from angle in degree
    in the interval \f$[-45, 45]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    tie(s, c) = fast_sincosd(x);
    @endcode

    is similar to:

    @code
    T0 c = fast_cosd(x);
    T0 s = fast_sind(x);
    @endcode

    @param a0

    @see @funcref{fast_sind}, @funcref{sincosd}, @funcref{fast_cosd}
    @return a pair of value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincosd_, fast_sincosd, 1)
  /*!
    Computes simultaneously sine and cosine from angle in degree
    in the interval \f$[-45, 45]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    s = fast_sincosd(x, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cosd(x);
    T0 s = fast_sind(x);
    @endcode

    @see @funcref{fast_sind}, @funcref{sincosd}, @funcref{fast_cosd}
    @param a0
    @param a1 L-Value that will receive the cosine of a0
    @return the sine of a0

  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincosd_, fast_sincosd,(A0 const&)(A1&),2)
  /*!
    Computes simultaneously sine and cosine from angle in degree
    in the interval \f$[-45, 45]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 c, s;
    fast_sincosd(x, s, c);
    @endcode

    is similar to:

    @code
    T0 c = fast_cosd(x);
    T0 s = fast_sind(x);
    @endcode

    @see @funcref{fast_sind}, @funcref{sincosd}, @funcref{fast_cosd}
    @param a0 input in degree
    @param a1 L-Value that will receive the sine of a0
    @param a2 L-Value that will receive the cosine of a0

    @return a pair of value of the same type as the parameter
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincosd_, fast_sincosd,(A0 const&)(A1&)(A2&),3)
}

#endif


