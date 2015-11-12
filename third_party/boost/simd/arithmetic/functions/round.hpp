//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  round generic tag

      Represents the round function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct round_ : ext::elementwise_<round_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<round_> parent;
    };
  }
  /*!
    Computes the rounded to nearest integer away from 0

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = round(x);
    @endcode

    Returns the nearest integer to x.

    @par Note:

    aways from 0 means that half integer values are rounded to the nearest
    integer of greatest absolute value

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round_, round, 1)
} }

#endif
