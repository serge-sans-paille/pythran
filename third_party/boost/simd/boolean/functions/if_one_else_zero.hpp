//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief if_one_else_zero generic tag

     Represents the if_one_else_zero function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_one_else_zero_ : ext::elementwise_<if_one_else_zero_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_one_else_zero_> parent;
    };
  }
  /*!
    If a0 is true returns zero else returns one

    @par Semantic:

    For every parameter of type T0 :

    @code
    T0::type r = if_one_else_zero(a0);
    @endcode

    is similar to:

    @code
    T0::type r = a0 ? one : zero;
    @endcode

    @par Alias:
    @c  if_one_else_zero, @c ifoneelsezero, @c sb2b;

    @see  @funcref{genmask}
    @par Note:

    @c T0:type denotes here @c T0 in most cases, but @c T if @c T0 is @c as_logical<T>

    @param a0

    @return a value of the type associated to the logical value a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_one_else_zero_, if_one_else_zero,    1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_one_else_zero_, ifoneelsezero,       1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_one_else_zero_, sb2b,                1)
} }

#endif


