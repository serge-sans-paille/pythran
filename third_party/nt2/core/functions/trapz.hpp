//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRAPZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRAPZ_HPP_INCLUDED

#include <nt2/include/functor.hpp>
namespace nt2
{
  namespace tag
  {
    struct trapz_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief Trapezoidal numerical integration



    @par Semantic

     - @code
       auto r = trapz(y);
       @endcode

       Computes an approximation of the integral of y via
       the trapezoidal method (with unit spacing).  to compute the integral
       for spacing different from one, multiply z by the spacing increment.

       for vectors, trapz(y) is the integral of y. for matrices, trapz(y)
       is a row vector with the integral over each column. for n-d
       arrays, trapz(y) works across the first non-singleton dimension.

     - @code
       auto r = trapz(x, y);
       @endcode

       computes the integral of y with respect to x using
       the trapezoidal method.  x must be a vector and y must a vector of the same
       length as the numel of x or an array whose first
       non-singleton dimension has  numel(x) elements.  trapz operates along this
       dimension.

    - @code
      auto r = trapz(x, y, n);
      @endcode

      or

    - @code
      auto r = trapz(y,dim)
      @endcode

      integrates across dimension dim
      of y. the length of x must be the same as size(y,n) and x gives the abscissae.

    @par Note:
    On the interval \f$[a, b]\f$ and value \f$y_a\f$, \f$y_b\f$, the trapezoidal integration formula write down:

    \f$ t = \frac{y_a+y_b}2 (b-a)\f$

    @see @funcref{firstnonsingleton}

    @param a0 Table expression to process if a1 is not present, or abscissae
    @param a1 Table expression to process or dimension along which to process
    @param a2 if present Dimension along which to process a0

    @return An expression eventually evaluating to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 1)

}


#endif
