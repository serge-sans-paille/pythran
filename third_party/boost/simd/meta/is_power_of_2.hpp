//==================================================================================================
/*!
  @file

  Defines the high-level interface for manipulating SIMD data.

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================

#ifndef BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED

#include <cstddef>

namespace boost { namespace simd
{

  template <std::size_t N>
  struct is_power_of_2_ {
    enum { value = !(N & (N - 1)) && N > 0 };
  };

  template <typename Integer>
  #if !defined(BOOST_NO_CONSTEXPR)
  constexpr
  #endif
  BOOST_FORCEINLINE bool is_power_of_2(Integer value)
  {
    return !(value & (value - 1)) && value > 0;
  }

} }

#endif
