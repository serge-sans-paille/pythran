//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_RSQRT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  rsqrt generic tag

      Represents the rsqrt function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct rsqrt_ : ext::elementwise_<rsqrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rsqrt_> parent;
    };
  }
  /*!
    Returns the inverse of the square root of the input.

    @par semantic:

    For any given value @c x of floating type @c T:

    @code
    T r = rsqrt(x);
    @endcode

    For signed type is similar to:

    @code
    T r = T(1)/sqrt(x)
    @endcode


    @param  a0

    @return      a value of the type of the input.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rsqrt_, rsqrt, 1)
} }

#endif


