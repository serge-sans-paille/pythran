//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXP_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXP_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief exp generic tag

     Represents the exp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exp_ : ext::elementwise_<exp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exp_> parent;
    };
  }
  /*!
    Computes the exponential function: \f$e^{x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = exp(a0);
    @endcode

    @see @funcref{exp2}, @funcref{exp10}, @funcref{pow}, @funcref{expm1}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exp_, exp, 1)
}

#endif

