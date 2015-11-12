//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
namespace tag
{
    /*!
      @brief  abss generic tag

      Represents the abss function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct abss_ : ext::elementwise_<abss_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<abss_> parent;
    };
  }
  /*!
    Computes the saturated absolute value of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = abss(x);
    @endcode

    is equivalent to:

    @code
    T r = (x == Valmin) ? Valmax : (x < T(0) ? -x : x);
    @endcode

    @par Note:

    The function always returns a positive value of the same type as the
    entry.

    This is generally equivalent to @c abs functor except for signed integer
    types for which \c abss(Valmin) is \c Valmax.

    @par Alias

    saturated_abs

    @see  @funcref{abs}, @funcref{sqr_abs}, @funcref{sqrs}
    @param  a0    value whose absolute value will be returned.

    @return         a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, abss, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, saturated_abs, 1)
} }

#endif
