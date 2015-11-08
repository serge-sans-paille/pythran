//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIGNNZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief signnz generic tag

     Represents the signnz function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct signnz_ : ext::elementwise_<signnz_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<signnz_> parent;
    };
  }
  /*!
    Returns the sign of a0. I.e. -1 or 1, according
    a0 is negative or positive.

    This function never returns zero (zero is considered positive for integers,
    for floating point numbers the bit of sign is taken into account and so
    we always have signnz(-z) == -signnz(z)).

    @par Semantic:

    @code
    T r = signnz(a0);
    @endcode

    is similar to:

    @code
    T r = is_nan(x) ? Nan<T>() : (is_negative(x) ? T(-1) : T(1));
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::signnz_, signnz, 1)
} }

#endif
