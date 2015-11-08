//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MINNUMMAG_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MINNUMMAG_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief minnummag generic tag

     Represents the minnummag function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct minnummag_ : ext::elementwise_<minnummag_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<minnummag_> parent;
    };
  }
  /*!
    Returns the input value which have the least absolute value, ignoring nan.

    @par Semantic:

    @code
    T r = minnummag(a0,a1);
    @endcode

    is similar to:

    @code
    T r =  isnan(a0) ? a1 : (isnan(a1) ? a0 : minmag(a0, a1));;
    @endcode

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minnummag_, minnummag, 2)
} }

#endif
