//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_LOGICAL_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_LOGICAL_ANDNOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief logical_andnot generic tag

     Represents the logical_andnot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_andnot_ : ext::elementwise_<logical_andnot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_andnot_> parent;
    };
  }
  /*!
    return the logical and of the first parameter and of the negation the second parameter
    the result type is logical type associated to the first parameter

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = logical_andnot(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = a0 && !a1;
    @endcode

    @par Alias:
    @c l_andnot

    @param a0

    @param a1

    @return a value of the logical type asssociated to the first parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_andnot_      , logical_andnot     , 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_andnot_      , l_andnot           , 2)
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
