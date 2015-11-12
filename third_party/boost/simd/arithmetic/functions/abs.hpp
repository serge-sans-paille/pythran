//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ABS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  abs generic tag

      Represents the abs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct abs_ : ext::elementwise_<abs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<abs_> parent;
    };
  }
  /*!
    Computes the absolute value of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = abs(x);
    @endcode

    is equivalent to:

    @code
    T r = x < T(0) ? -x : x;
    @endcode

    @par Note:

    Take care that for signed integers the absolute value of @c Valmin is
    @c Valmin (thus negative!).
    This is a side effect of the 2-complement representation of integers.
    To avoid this, you can use the @c abss saturated functor or convert the
    input parameter to a larger type before taking the absolute value.

    @par Alias

    modulus

    @see  @funcref{abss}, @funcref{sqr_abs}, @funcref{sqrs}
    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, abs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, modulus, 1)
} }

#endif
