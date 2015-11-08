//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIGN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief sign generic tag

     Represents the sign function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sign_ : ext::elementwise_<sign_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sign_> parent;
    };
  }
  /*!
    Returns the sign of a0. I.e. -1, 0 or 1, according
    a0 is less than zero, zero or greater than zero.
    For floating sign of nan is nan

    @par Semantic:

    @code
    T r = sign(x);
    @endcode

    is similar to:

    @code
    T r = (x > 0) ? T(1) : ((x < 0) ? T(-1) : ((x == 0) ? 0 : Nan<T>()));
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sign_, sign, 1)
} }

#endif
