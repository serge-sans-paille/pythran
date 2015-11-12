//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXP10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXP10_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief exp10 generic tag

     Represents the exp10 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exp10_ : ext::elementwise_<exp10_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exp10_> parent;
    };
  }
  /*!
    Computes the base ten exponential function: \f$10^{x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = exp10(x);
    @endcode

    is similar to:

    @code
    T0 r = exp(x*log_10<T0>());
    @endcode

    @par Note:

    provisions are made for obtaining a flint result from a flint input

    @see @funcref{exp2}, @funcref{exp}, @funcref{pow}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exp10_, exp10, 1)
}

#endif

