//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_RROL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_RROL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  rrol generic tag

      Represents the rrol function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct rrol_ : ext::elementwise_<rrol_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rrol_> parent;
    };
  }
  /*!
    Returns the first entry rotated left or right
    by the absolute value of the second entry,
    according to its sign.

    @par semantic:
    For any given value @c x of type @c T, n  of type @c I:

    @code
    T r = rrol(x, n);
    @endcode

    @param  a0
    @param  a1

    @return      a value of the same type as the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rrol_, rrol, 2)
} }

#endif
