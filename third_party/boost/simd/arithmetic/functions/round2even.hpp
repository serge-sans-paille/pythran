//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND2EVEN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  round2even generic tag

      Represents the round2even function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct round2even_ : ext::elementwise_<round2even_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<round2even_> parent;
    };
  }
  /*!
    Computes the rounded to even value of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = round2even(x);
    @endcode

    Returns the nearest integer to x.

    @par Note:

    to even means that half integer values are rounded to the nearest
    even value

    @par Alias:
    @c rint

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round2even_, round2even, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round2even_, rint, 1)
} }

#endif

