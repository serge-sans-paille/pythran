//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_BETA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_BETA_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief beta generic tag

     Represents the beta function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct beta_ : ext::elementwise_<beta_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<beta_> parent;
    };
  }
  /*!
    Computes Beta function :
        \f$ B(a_0,a_1)=\int_0^1 t^{a_0-1}(1-t)^{a_1-1}\mbox{d}t\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = beta(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = gamma(a0)*gamma(a1)/gamma(a0+a1);
    @endcode

    @see @funcref{gamma}
    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::beta_, beta, 2)
}

#endif
