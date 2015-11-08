//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_LOOKUP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief lookup generic tag

     Represents the lookup function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct lookup_ : ext::unspecified_<lookup_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<lookup_> parent;
    };
  }
  /*!
    shuffles the elements of a1 using indices in a2

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = lookup(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r;
    for(size_t i=0; i < boost::simd::meta::cardinal_of<T0>::value; i++)
      r[i] = a0[a1[i]];
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the first parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lookup_, lookup, 2)
} }

#endif
