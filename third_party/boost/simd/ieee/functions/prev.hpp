//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_PREV_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_PREV_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief prev generic tag

     Represents the prev function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct prev_ : ext::elementwise_<prev_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<prev_> parent;
    };
  }
  /*!
    in the type A0 of a0, the greatest A0 strictly less than a0

    @par Semantic:

    @code
    T r = prev(a0);
    @endcode

    computes the greatest value strictly less than a0 in type T

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::prev_, prev, 1)
} }

#endif
