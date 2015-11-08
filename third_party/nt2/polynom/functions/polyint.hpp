//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_POLYINT_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_POLYINT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief polyint generic tag

     Represents the polyint function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct polyint_ : ext::elementwise_<polyint_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<polyint_> parent;
    };
  }
  /*!
    returns a polynomial representing the primitive null at zero
    of polynomial p

    @par semantic:

    For every expression representing a polynomial

    @code
    auto r = polyint(p);
    @endcode

    is such that if p represents \f$\displaystyle \sum_0^n a_i x^i\f$ then r represents
    \f$\displaystyle \sum_0^n \frac{a_ix^{i+1}}{i+1}\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyint_,polyint, 1)
  /*!
    returns a polynomial representing the primitive null at zero
    of polynomial p, using a scalar constant of integration k.
    @par semantic:

    For every expression representing a polynomial

    @code
    auto r = polyint(p, k);
    @endcode

    is such that if p represents \f$\displaystyle \sum_0^n a_i x^i\f$ then r represents
    \f$\displaystyle k+\sum_0^n \frac{a_ix^{i+1}}{i+1}\f$

    @param a0
    @param a1

    @return a value of the same type as the parameter
  **/  NT2_FUNCTION_IMPLEMENTATION(tag::polyint_,polyint, 2)
}
#endif
