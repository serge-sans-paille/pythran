//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_POLYDER_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_POLYDER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief polyder generic tag

     Represents the polyder function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct polyder_ : ext::elementwise_<polyder_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<polyder_> parent;
    };
  }
  /*!
    Derivative of a polynomial

    @par Semantic:

    For every parameter p representing a polynomial

    @code
    auto r = polyder(p);
    @endcode

    is such that if p represents \f$\displaystyle \sum_0^n a_i x^i\f$ then r represents
    \f$\displaystyle \sum_1^n ia_ix^{i-1}\f$


    @param a0
    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyder_,polyder, 1)
  /*!
    Derivative of a polynomial product

    @par Semantic:

    For every parameter p, q representing a polynomial

    @code
    auto r = polyder(p, q);
    @endcode

    is similar to

    @code
    auto r = polyder(conv(p, q));
    @endcode

    without computing the product.

    @param a0
    @param a1


    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyder_,polyder, 2)
}
#endif
