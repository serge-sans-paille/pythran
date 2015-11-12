//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_HIGH_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief split_high generic tag

     Represents the split_high function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct split_high_ : ext::unspecified_<split_high_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<split_high_> parent;
    };
  }

  /*!
    @brief SIMD register type-based split_high

    @c split_high extract the higher half of a SIMD register and convert it
    to the appropriate SIMD register type of corresponding cardinal.

    @see split_low, split, slice
    @param a0 Value to process

    @return THe higher half of a0 converted to the appropriate SIMD type
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_high_, split_high, 1)
} }

#endif
