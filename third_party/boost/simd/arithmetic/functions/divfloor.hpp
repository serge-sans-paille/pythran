//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVFLOOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  divfloor generic tag

      Represents the divfloor function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct divfloor_ : ext::elementwise_<divfloor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<divfloor_> parent;
    };
  }
  /*!
    Computes the floor of the division.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = divfloor(x, y);
    @endcode

    The code is similar to:

    @code
    T r = floor(x/y);
    @endcode

    for integral types, if y is null, it returns Valmax or Valmin
    if x is positive (resp. negative) and 0 if x is null.
    Take also care that dividing Valmin by -1 for signed integral types has
    undefined behaviour.

    @see  @funcref{divides}, @funcref{fast_divides}, @funcref{rec}, @funcref{fast_rec}, @funcref{divs}, @funcref{divfix},
    @funcref{divround}, @funcref{divround2even}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divfloor_, divfloor, 2)
} }

#endif
