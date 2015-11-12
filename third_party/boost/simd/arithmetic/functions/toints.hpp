//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINTS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  toints generic tag

      Represents the toints function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct toints_ : ext::elementwise_<toints_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<toints_> parent;
    };
  }
  /*!
    Convert to integer by saturated truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = toints(x);
    @endcode

    The code is similar to:

    @code
    as_integer<T> r = static_cast<as_integer<T> >(saturate<as_integer<T> >(x))
    @endcode

    @par Notes:

    The Inf -Inf and Nan values are treated properly and go respectively to
    Valmax, Valmin and Zero of the destination integral type
    All values superior (resp.) less than Valmax (resp. Valmin) of the return type
    are saturated accordingly.

    @par Alias

    @c ifix,  @c itrunc, @c saturated_toint

    @param  a0

    @return      a value of the integer same type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, toints, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, ifix, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, itrunc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, saturated_toint, 1)

} }

#include <boost/simd/operator/specific/common.hpp>

#endif
