//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/U.B.P.
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ. Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SQR_ABS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  sqr_abs generic tag

      Represents the sqr_abs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct sqr_abs_ : ext::elementwise_<sqr_abs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sqr_abs_> parent;
    };
  }
  /*!
    Computes the square of the absolute value of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = sqr_abs(x);
    @endcode

    is equivalent to:

    @code
    T r = sqr(abs(x));
    @endcode

    @par Alias

    @c sqr_modulus

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqr_abs_, sqr_abs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqr_abs_, sqr_modulus, 1)
} }

#endif


