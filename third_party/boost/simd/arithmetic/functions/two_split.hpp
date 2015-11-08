//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TWO_SPLIT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
  @file
  @brief Definition of the two_split function
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /// @brief Hierarchy tag for two_split function
    struct two_split_ : ext::elementwise_<two_split_>
    {
      typedef ext::elementwise_<two_split_> parent;
    };
  }

  /*!
    @brief

    For any real @c a0, two_split computes two reals @c r0 and @c r1 so that:

    @code
    a0 = r0+r1
    @endcode

    and where @c r0 and @c r1 bit pattern don't overlap.

    @param a0 Value to split

    @return A Fusion Sequence containing @c a0+a1 and the residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::two_split_, two_split, 1)

  /*!
    @brief

    For any real @c a0, two_split computes two reals @c r0 and @c r1 so that:

    @code
    a0 = r0+r1
    @endcode

    and where @c r0 and @c r1 bit pattern don't overlap.

    @param a0 Value to split
    @param a1 L-Value that will receive @c a0+a1

    @return The sum residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::two_split_, two_split
                                            , (A0 const&)(A1&)
                                            , 2
                                            )

  /*!
    @brief

    For any real @c a0, two_split computes two reals @c r0 and @c r1 so that:

    @code
    a0 = r0+r1
    @endcode

    and where @c r0 and @c r1 bit pattern don't overlap.

    @param a0 Value to split
    @param a1 L-Value that will receive @c a0+a1.
    @param a2 L-Value that will receive @c a0+a1 residual.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::two_split_, two_split
                                            , (A0 const&)(A1&)(A2&)
                                            , 3
                                            )
} }

#endif
