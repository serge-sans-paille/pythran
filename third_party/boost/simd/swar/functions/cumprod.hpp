//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef BOOST_SIMD_SWAR_FUNCTIONS_CUMPROD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_CUMPROD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/constant/constants/one.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  cumprod generic tag

      Represents the cumprod function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct cumprod_ : ext::cumulative_<cumprod_, tag::multiplies_, tag::One>
    {
      /// @brief Parent hierarchy
      typedef ext::cumulative_<cumprod_, tag::multiplies_, tag::One> parent;
    };
  }
  /*!
    Computes the cumulated product of the vector elements

    Take care that overflow is very easy to get here especially for integral types
    char and unsigned char always overflow except for 0 and 1 !

    @par semantic:
    For any given vector @c x of type @c T:

    @code
    T r = cumprod(x);
    @endcode

    The function coincide with plus for floating point parameters.
    For integers is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i]*= r[i-1];
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumprod_, cumprod, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumprod_, cumprod, 2)
} }

#endif
