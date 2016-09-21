//==================================================================================================
/*!
  @file

  Defines the native_cardinal meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED
#define BOOST_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/meta/expected_cardinal.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    @brief Expected cardinal of current architecture register

    Computes the cardinal of a SIMD register containing elements of type @c Type on
    the currently selected hardware

    @tparam Type      Element type of the expected register
  **/
  template<typename T>
  struct  native_cardinal : expected_cardinal<T, BOOST_SIMD_DEFAULT_SITE>
  {};
} }

#endif
