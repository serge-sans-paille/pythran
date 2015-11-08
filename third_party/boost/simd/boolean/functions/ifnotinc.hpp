//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTINC_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTINC_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief ifnotinc generic tag

     Represents the ifnotinc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ifnotinc_ : ext::elementwise_<ifnotinc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ifnotinc_> parent;
    };
  }
  /*!
    Increments a value by 1 if a predicate is false.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T1 r = ifnotinc(a0,a1);
    @endcode

    is similar to:

    @code
    T1 r = a0 ? a1 : a1+one;
    @endcode

    @par Alias:
    @c selnotinc

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotinc_, ifnotinc, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotinc_, selnotinc,  2)
} }

#endif
