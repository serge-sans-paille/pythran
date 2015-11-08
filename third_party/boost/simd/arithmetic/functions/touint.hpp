//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOUINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOUINT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  touint generic tag

      Represents the touint function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct touint_ : ext::elementwise_<touint_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<touint_> parent;
    };
  }
  /*!
    Convert to unsigned integer by truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T, unsigned> r = touint(x);
    @endcode

    The code is similar to:

    @code
    as_integer<T, unsigned> r = static_cast<as_integer<T, unsigned> >(x)
    @endcode

    @par Notes:

    @c toint cast a floating value to the signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid or negative
    entries is not defined and possibly unpredictable.

    If you intend to use nans, infs or negative entries, consider using touints instead.

    @par Alias

    fast_touint

    @param  a0

    @return      a value of the unsigned integer type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::touint_, touint, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::touint_, fast_touint, 1)

} }

#endif

