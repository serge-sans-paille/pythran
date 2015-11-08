//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief if_zero_else generic tag

     Represents the if_zero_else function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_zero_else_ : ext::elementwise_<if_zero_else_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_zero_else_> parent;
    };
  }
  /*!
    If a0 is true returns zero else returns a1

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T r = if_zero_else(a0,a1);
    @endcode

    is similar to:

    @code
    T r = a0 ? zero :a1;
    @endcode

    @par Alias:
    @c if_zero_else,
    @c ifzeroelse,
    @c ifnot_else_zero,
    @c ifnotelsezero

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, if_zero_else,    2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifzeroelse,      2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifnot_else_zero, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifnotelsezero,   2)
} }

#endif


