//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief safe_min generic tag

     Represents the safe_min function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct safe_min_ : ext::elementwise_<safe_min_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<safe_min_> parent;
    };
  }
  /*!
    Returns a safe mininimal value relative to the input, i.e. a
    value which will not underflow when divided by the input.

    @par Semantic:

    @code
    T r = safe_min(x);
    @endcode

    is similar to:

    @code
    T r =  x ? Sqrtsmallestposval<T>()*abs(x);
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::safe_min_, safe_min, 1)
} }

#endif
