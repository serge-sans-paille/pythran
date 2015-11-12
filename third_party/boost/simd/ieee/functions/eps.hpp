//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief eps generic tag

     Represents the eps function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct eps_ : ext::elementwise_<eps_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<eps_> parent;
    };
  }
  /*!
    Except for numbers whose absolute value is smaller than Smallestpositivevalue,
    @c eps(x) returns 2^(exponent(x))*Eps


    @par Semantic:

    @code
    T r = eps(a0);
    @endcode

    is similar to:

    @code

    if T is floating
      r = 2^(exponent(x))*Eps<T>
    else if T is integral
      r = 1;
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::eps_, eps, 1)
} }

#endif
