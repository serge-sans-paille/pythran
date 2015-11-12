//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MAXNUM_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MAXNUM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief maxnum generic tag

     Represents the maxnum function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct maxnum_ : ext::elementwise_<maxnum_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<maxnum_> parent;
    };
  }
  /*!
    Returns the maximum value, ignoring nans.

    @par Semantic:

    @code
    T r = maxnum(a0,a1);
    @endcode

    is similar to:

    @code
    T r = (is_nan(a0) ? a1 : (isnan(a1) ? a0 : max(a0, a1));
    @endcode

    @par Alias:
    @c fmax

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::maxnum_, maxnum, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::maxnum_, fmax, 2)
} }

#endif
