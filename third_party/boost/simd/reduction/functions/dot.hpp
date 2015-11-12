//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_DOT_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_DOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief dot generic tag

     Represents the dot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct dot_ : ext::unspecified_<dot_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<dot_> parent;
    };
  }
  /*!
    returns the dot product of the two vector arguments

    @par Semantic:

    For every parameters of type T0:

    @code
    scalar_of<T0> r = dot(a0,a1);
    @endcode

    is similar to:

    @code
    scalar_of<T0> r = sum(a0*conj(a1));
    @endcode

    @param a0

    @param a1

    @return a value of the scalar type associated to the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dot_, dot, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dot_, dot, 3)
} }
#endif

