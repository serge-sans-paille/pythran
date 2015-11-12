//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sincosd function
    struct sincosd_ : ext::elementwise_<sincosd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sincosd_> parent;
    };
  }
  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    tie(s, c) = sincosd(x);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @see @funcref{fast_sincosd}, @funcref{sincos}, @funcref{sincospi}
    @param a0 angle in degree

    @return A Fusion Sequence containing the sind and cosd of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sincosd_, sincosd, 1)

  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    s = sincosd(x, c);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @param a0 angle in degree
    @param a1 L-Value that will receive the sind of @c a0

    @return A Fusion Sequence containing the cosd of @c a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&),2)

  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    sincosd(x, s, c);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @param a0 angle in degree
    @param a1 L-Value that will receive the sind of @c a0
    @param a2 L-Value that will receive the cosd of @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&)(A2&),3)

    }

#endif

