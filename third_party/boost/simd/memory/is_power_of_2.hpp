//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_IS_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements is_power_of_2
**/

#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Power of two compliance predicate for integers

    Checks if a value is a non-zero power of two.

    @par Semantic:

    For any integer @c v :

    @code
    bool r = is_power_of_2(v);
    @endcode

    is equivalent to

    @code
    bool r = (!(value & (value - 1)) && value);
    @endcode

    If @c a is not a power of two, an assertion is triggered.

    @usage{memory/is_power_of_2.cpp}

    @param value  Value to check

    @return A boolean indicating if @c value is a non-zero power of two
  **/
  template<typename Integer> BOOST_FORCEINLINE
  bool is_power_of_2(Integer value)
  {
    return (!(value & (value - 1)) && value);
  }
} }

#endif
