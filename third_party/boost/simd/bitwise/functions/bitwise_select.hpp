//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_BITWISE_SELECT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  bitwise_select generic tag

      Represents the bitwise_select function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct bitwise_select_ : ext::elementwise_<bitwise_select_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitwise_select_> parent;
    };
  }
  /*!
    Returns the bitwise selection of bits from the second
    or third operand according to the setting of the bits
    of the first operand

    @par semantic:
    For any given value @c x, of type @c T1, @c y of type @c T2 and @c z of type @c T2
    of same memory size:

    @code
    T2 r = bitwise_select(x, y, z);
    @endcode

    The code is equivalent to:

    @code
    T2 r = (x&y)|(z&~y);
    @endcode

    @par Alias

    b_select

    @param  a0 selector
    @param  a1 bits selected for a0 bits that are on
    @param  a2 bits selected for a0 bits that are off

    @return      a value of the same type as the second input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_select_, bitwise_select, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_select_, b_select, 3)
} }

#endif

