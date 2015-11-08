//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTDEC_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTDEC_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief ifnotdec generic tag

     Represents the ifnotdec function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ifnotdec_ : ext::elementwise_<ifnotdec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ifnotdec_> parent;
    };
  }

  /*!
    Decrements a value by 1 if a predicate is False.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T1 r = ifnotdec(a0,a1);
    @endcode

    is similar to:

    @code
    T1 r = a0 : a1 : a1-one;
    @endcode

    @par Alias:
    @c selnotdec

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotdec_, ifnotdec, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotdec_, selnotdec,  2)
} }

#endif
