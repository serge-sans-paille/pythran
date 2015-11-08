//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_CTZ_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_CTZ_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  ctz generic tag

      Represents the ctz function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ctz_ : ext::elementwise_<ctz_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ctz_> parent;
    };
  }

  /*!
    @brief Returns the bit count of trailing zeroes

    Finds the first bit set in a0, and returns the index of that bit, 0 being
    the least significant bit index.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T,unsigned> r = ctz(x);
    @endcode

    @see  @funcref{clz}, @funcref{popcnt}
    @param a0 Value to check

    @return An unsigned integral value containing the index of the first bit
            set in a0.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ctz_, ctz, 1)
} }

#endif
