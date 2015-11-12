//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SQRT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  sqrt generic tag

      Represents the sqrt function in generic contexts.

      @par Models:
    **/
    struct sqrt_ : ext::elementwise_<sqrt_>
    {
      typedef ext::elementwise_<sqrt_> parent;
    };
  }
  /*!
    Computes the square root of its parameter. For integers it is the
    truncation of the real square root.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = sqrt(x);
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqrt_, sqrt, 1)
} }

#endif


