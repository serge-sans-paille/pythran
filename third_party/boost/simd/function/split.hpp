//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLIT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    Function object implementing split capabilities

    Split a SIMD register @c x in two SIMD registers of half the
    cardinal of @c x containing the same value than @c x but converted to
    their associated upgraded type.


    @par Header <boost/simd/function/split.hpp>

    @param x Value to split
    @return An array containing the two upgraded part of its argument.
  **/
  std::array<upgrade_t<Value>, 2> split(Value const& x);
} }
#endif

#include <boost/simd/function/simd/split.hpp>

#endif
