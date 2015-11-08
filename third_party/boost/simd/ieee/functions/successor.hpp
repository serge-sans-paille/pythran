//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief successor generic tag

     Represents the successor function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct successor_ : ext::elementwise_<successor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<successor_> parent;
    };
  }
  /*!
    Returns the least element strictly greater than the parameter

    @par Semantic:

    @code
    T r = successor(x);
    @endcode

    computes the least value strictly greater than x in its type

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 1)
  /*!
    Returns the n-th least element strictly greater than the parameter

    @par Semantic:

    @code
    T r = successor(x,n);
    @endcode

    computes the @c n-th least value strictly greater than x in its type

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 2)
} }

#endif
