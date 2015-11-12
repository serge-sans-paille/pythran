//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_GROUPS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_GROUPS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief groups generic tag

     Represents the groups function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct groups_ : ext::elementwise_<groups_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<groups_> parent;
    };
  }
  /*!
    take two SIMD vectors of same type and elements of size n
    and return a vector collecting the two in a vector in which
    the elements have size n/2 properly saturated.

    Of course the applicability is conditioned by the existence of compatible
    SIMD vector types

    @par Semantic:

    For every parameters of type T0

    @code
    T0 r = groups(a0, a1);
    @endcode

    is similar to:

    @code
    downgrade<T0> r;
    for(int i=0;i < T0::static_size; ++i)
      r[i] = a0[i];
      r[i+T0::static_size] = a1[i];
    @endcode

    @par Alias:
    @c demotes, @c narrows

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::groups_, groups, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::groups_, demotes, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::groups_, narrows, 1)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::groups_, groups, 2)
} }

#endif
