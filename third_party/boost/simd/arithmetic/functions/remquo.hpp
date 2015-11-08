//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_REMQUO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
      @brief  remquo generic tag

      Represents the remquo function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct remquo_ : ext::elementwise_<remquo_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<remquo_> parent;
    };
  }

  /*!
    @brief Remainder and part of quotient

    remquo computes the remainder and part of the quotient upon division of
    @c a0 by @c a1. By design, the value of the remainder is the same as that
    computed by the remainder function. The value of the computed quotient has
    the sign of @c a0/a1 and agrees with the actual quotient in at least the low
    order 3 bits.

    @param a0 Dividend value
    @param a1 Divisor value

    @return A Fusion Sequence containing the two remainder and partial quotient
    of @c a0/a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remquo_, remquo, 2)

  /*!
    @brief Remainder and part of quotient

    remquo computes the remainder and part of the quotient upon division of
    @c a0 by @c a1. By design, the value of the remainder is the same as that
    computed by the remainder function. The value of the computed quotient has
    the sign of @c a0/a1 and agrees with the actual quotient in at least the low
    order 3 bits.

    @param a0 Dividend value
    @param a1 Divisor value
    @param a2 L-Value that will receive the partial quotient of @c a0

    @return The remainder of @c a0/a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::remquo_, remquo
                                            , (A0 const&)(A1 const&)(A2&)
                                            , 3
                                            )

  /*!
    @brief Remainder and part of quotient

    remquo computes the remainder and part of the quotient upon division of
    @c a0 by @c a1. By design, the value of the remainder is the same as that
    computed by the remainder function. The value of the computed quotient has
    the sign of @c a0/a1 and agrees with the actual quotient in at least the low
    order 3 bits.

    @param a0 Dividend value
    @param a1 Divisor value
    @param a2 L-Value that will receive the remainder of @c a0
    @param a3 L-Value that will receive the partial quotient of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::remquo_, remquo
                                            , (A0 const&)(A1 const&)(A2&)(A3&)
                                            , 4
                                            )
} }

#endif
