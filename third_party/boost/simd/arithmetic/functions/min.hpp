//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MIN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  min generic tag

      Represents the min function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct min_ : ext::elementwise_<min_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<min_> parent;
    };
  }
  /*!
    Computes the smallest of its parameter.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    T r = min(x, y);
    @endcode

    is similar to:

    @code
    T r =  if (x < y) ? x : y;
    @endcode

    @param  a0
    @param  a1

    @return an value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::min_, min, 2)
} }

#endif


