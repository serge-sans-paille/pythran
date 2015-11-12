//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MAXMAG_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MAXMAG_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief maxmag generic tag

     Represents the maxmag function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct maxmag_ : ext::elementwise_<maxmag_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<maxmag_> parent;
    };
  }
  /*!
    Returns the input value which have the greatest absolute value.

    @par Semantic:

    @code
    T r = maxmag(a0,a1);
    @endcode

    is similar to:

    @code
    T r = abs(a0) > abs(a1) ? a0 : abs(a1) > abs(a0) ? a1 : max(a0, a1);
    @endcode

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::maxmag_, maxmag, 2)
} }

#endif
