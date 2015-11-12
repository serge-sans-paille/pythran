//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief split generic tag

     Represents the split function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct split_ : ext::elementwise_<split_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<split_> parent;
    };
  }

  /*!
    @brief SIMD register type-based split

    @c split splits a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v but transtyped to
    their associated scalar type.

    @par Alias:
    @c promote, @c widen

    @param a0 Value to split

    @return A Fusion Sequence containing the two sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_, split, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_, promote, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_, widen, 1)

  /*!
    @brief SIMD register type-based split

    @c split splits a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v but transtyped to
    their associated scalar type.

    @param a0 Value to split
    @param a1 L-Value that will receive the second sub-part of @c a0

    @return The first sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::split_, split
                                            , (A0 const &)(A1&)
                                            , 2
                                            )

  /*!
    @brief SIMD register type-based split

    @c split splits a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v but transtyped to
    their associated scalar type.

    @param a0 Value to split
    @param a1 L-Value that will receive the first sub-part of @c a0
    @param a2 L-Value that will receive the second sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::split_, split
                                            , (A0 const &)(A1&)(A1&)
                                            , 2
                                            )
} }

#endif
