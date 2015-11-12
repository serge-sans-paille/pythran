//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVROUND2EVEN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  divround2even generic tag

      Represents the divround2even function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct divround2even_ : ext::elementwise_<divround2even_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<divround2even_> parent;
    };
  }
  /*!
    Computes the round2even of the division.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = divround2even(x, y);
    @endcode

    The code is similar to:

    @code
    T r = round2even(x/y);
    @endcode

    for integral types, if y is null, it returns Valmax or Valmin
    if x is positive (resp. negative) and 0 if x is null.
    Take also care that dividing Valmin by -1 for signed integral types has
    undefined behaviour.

    @see  @funcref{divides}, @funcref{fast_divides}, @funcref{rec}, @funcref{fast_rec}, @funcref{divs}, @funcref{divfloor},
    @funcref{divceil}, @funcref{divround}, @funcref{divfix}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divround2even_, divround2even, 2)
} }

#endif
