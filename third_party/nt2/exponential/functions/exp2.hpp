//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXP2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXP2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief exp2 generic tag

     Represents the exp2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exp2_ : ext::elementwise_<exp2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exp2_> parent;
    };
  }
  /*!
    base two exponential function: \f$2^{x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = exp2(x);
    @endcode

    is similar to:

    @code
    T0 r = pow(T(2), x);
    @endcode

    @par Note:
    provisions are made for otaining a flint result from a flint input

    @see @funcref{exp}, @funcref{exp10}, @funcref{pow}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exp2_, exp2, 1)
}

#endif

