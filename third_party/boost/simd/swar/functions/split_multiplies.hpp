//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_MULTIPLIES_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /// @brief Hierarchy tag for split_multiplies function
    struct split_multiplies_ : ext::elementwise_<split_multiplies_>
    {
      typedef ext::elementwise_<split_multiplies_> parent;
    };
  }

  /*!
    @brief SIMD register type-based multiplies and split

    @c split_multiplies multiplies two x-bit SIMD registers and returns two 2x-bit registers
    each having half the cardinal of the original inputs.

    @param a0 LHS of multiplication
    @param a1 RHS of multiplication

    @return A Fusion Sequence containing the result of @c a0 * @c a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_multiplies_, split_multiplies, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_multiplies_, full_mul, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_multiplies_, wide_mul, 2)

  /*!
    @brief SIMD register type-based multiplies and split

    @c split_multiplies multiplies two x-bit SIMD registers and returns two 2x-bit registers
    each having half the cardinal of the original inputs.

    @param a0 LHS of multiplication
    @param a1 RHS of multiplication
    @param a2 L-Value that will receive the second sub-part of @c a0 * @c a1

    @return The first sub-part of @c a0 * @c a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::split_multiplies_, split_multiplies
                                            , (A0 const &)(A0 const&)(A1&)
                                            , 2
                                            )

  /*!
    @brief SIMD register type-based multiplies and split

    @c split_multiplies multiplies two x-bit SIMD registers and returns two 2x-bit registers
    each having half the cardinal of the original inputs.

    @param a0 LHS of multiplication
    @param a1 RHS of multiplication
    @param a2 L-Value that will receive the first sub-part of @c a0 * @c a1
    @param a3 L-Value that will receive the second sub-part of @c a0 * @c a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::split_multiplies_, split_multiplies
                                            , (A0 const &)(A0 const&)(A1&)(A1&)
                                            , 2
                                            )
} }

#endif
