//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_ATANH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_ATANH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atanh generic tag

     Represents the atanh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atanh_ : ext::elementwise_<atanh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atanh_> parent;
    };
  }
  /*!
    Returns the hyperbolic tangent argument \f$\frac12\log\frac{a_0^2-1}{a_0^2+1}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = atanh(a0);
    @endcode

    is similar to:

    @code
    T0 r = Half<T0>()*log((x*x-one)/(x*x+one));
    @endcode

    @see @funcref{log}, @funcref{Half}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atanh_, atanh, 1)
}

#endif

