//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_FRAC_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_FRAC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief frac generic tag

     Represents the frac function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct frac_ : ext::elementwise_<frac_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<frac_> parent;
    };
  }
  /*!
    This function returns the fractional part of the input

    @par Semantic:

    @code
    T r = frac(a0);
    @endcode

    is similar to:

    @code
    T r =  a0-trunc(a0);
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::frac_, frac, 1)
} }

#endif
