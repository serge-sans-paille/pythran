//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_ILOGB_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief ilogb generic tag

     Represents the ilogb function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ilogb_ : ext::elementwise_<ilogb_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ilogb_> parent;
    };
  }
  /*!
    This function returns the integer truncation
    of the base 2 logarithm of a0.
    It coincides with the exponent function
    on all platforms supported.

    @par Semantic:

    @code
    T r = ilogb(a0);
    @endcode

    is similar to:

    @code
    T r = toints(log2(a0));
    @endcode

    @see @funcref{exponent}
    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ilogb_, ilogb, 1)
} }

#endif
