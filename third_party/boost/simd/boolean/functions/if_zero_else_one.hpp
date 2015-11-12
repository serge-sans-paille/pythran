//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief if_zero_else_one generic tag

     Represents the if_zero_else_one function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_zero_else_one_ : ext::elementwise_<if_zero_else_one_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_zero_else_one_> parent;
    };
  }
  /*!
    If a0 is true returns zero else returns a1

    @par Semantic:

    For every parameters of types respectively T0:

    @code
    T r = if_zero_else_one(a0);
    @endcode

    is similar to:

    @code
    T r =  a0 ? zero :  one;
    @endcode

    @par Alias:
    @c  if_zero_else_one, @c ifzeroelseone;

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_one_, if_zero_else_one,   1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_one_, ifzeroelseone,      1)
} }

#endif


