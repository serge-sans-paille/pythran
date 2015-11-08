//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TWO_ADD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TWO_ADD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
  @file
  @brief Definition of the two_add function
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /// @brief Hierarchy tag for two_add function
    struct two_add_ : ext::elementwise_<two_add_>
    {
      typedef ext::elementwise_<two_add_> parent;
    };
  }

  /*!
    @brief

    For any two reals @c a0 and @c a1 two_add computes two reals
    @c r0 and @c r1 so that:

    @code
    r0 = a0 + a1
    r1 = r0 -(a0 + a1)
    @endcode

    using perfect arithmetic. Its main usage is to be able to compute
    sum of reals and the residual error using IEEE 754 arithmetic.

    @param a0 First parameter of the sum
    @param a1 Second parameter of the sum

    @return A Fusion Sequence containing @c a0+a1 and the residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::two_add_, two_add, 2)

  /*!
    @brief

    For any two reals @c a0 and @c a1 two_add computes two reals
    @c r0 and @c r1 so that:

    @code
    r0 = a0 + a1
    r1 = r0 -(a0 + a1)
    @endcode

    using perfect arithmetic. Its main usage is to be able to compute
    sum of reals and the residual error using IEEE  754 arithmetic.

    @param a0 First parameter of the sum
    @param a1 Second parameter of the sum
    @param a2 L-Value that will receive @c a0+a1

    @return The sum residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::two_add_, two_add
                                            , (A0 const&)(A1 const&)(A2&)
                                            , 3
                                            )

  /*!
    @brief

    For any two reals @c a0 and @c a1 two_add computes two reals
    @c r0 and @c r1 so that:

    @code
    r0 = a0 + a1
    r1 = r0 -(a0 + a1)
    @endcode

    using perfect arithmetic. Its main usage is to be able to compute
    sum of reals and the residual error using IEEE  754 arithmetic.

    @param a0 First parameter of the sum
    @param a1 Second parameter of the sum
    @param a2 L-Value that will receive @c a0+a1.
    @param a3 L-Value that will receive @c a0+a1 residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::two_add_, two_add
                                            , (A0 const&)(A1 const&)(A2&)(A3&)
                                            , 4
                                            )
} }

#endif
