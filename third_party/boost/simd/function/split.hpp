//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLIT_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Function object implementing split capabilities

    Split a SIMD register @c x in two SIMD registers of half the
    cardinal of @c x containing the same value than @c x but converted to
    their associated upgraded type.

    @param v0 Value to split
    @return An array containing the two upgraded part of its argument.
  **/
  std::array<upgrade_t<Value>,2> split(Value const & v0);
#endif
} }

#include <boost/simd/function/simd/split.hpp>

#endif
