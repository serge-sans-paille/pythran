//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_INBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_INBTRUE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief inbtrue generic tag

     Represents the inbtrue function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct inbtrue_ : ext::unspecified_<inbtrue_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<inbtrue_> parent;
    };
  }
  /*!
    Returns the number of non zero elements of the input SIMD vector.

    @par Semantic:

    For every parameter of type T0

    @code
    size_t r = inbtrue(a0);
    @endcode

    is similar to:

    @code
    size_t r = sum(if_one_else_zero(a0));
    @endcode

    @param a0

    @return a size_t value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inbtrue_, inbtrue, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inbtrue_, inbtrue, 2)
} }
#endif

