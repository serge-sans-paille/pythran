//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SELDEC_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SELDEC_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief seldec generic tag

     Represents the seldec function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct seldec_ : ext::elementwise_<seldec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<seldec_> parent;
    };
  }

  /*!
    Decrements a value by 1 if a predicate is true.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T1 r = seldec(a0,a1);
    @endcode

    is similar to:

    @code
    T1 r = a0 : a1-one : a1;
    @endcode

    @par Alias:
    @c ifdec

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seldec_, seldec, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seldec_, ifdec,  2)
} }

#endif
