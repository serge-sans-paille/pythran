//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
 /*!
    @ingroup group-swar
    Function object implementing split_high capabilities

    SIMD register type-based split_high

    @c split_high extract the higher half of a SIMD register and convert it
    to the appropriate SIMD register type of corresponding cardinal.

    @see split_low, split, slice
  **/
  const boost::dispatch::functor<tag::split_high_> split_high = {};
#endif
} }

#include <boost/simd/function/simd/split_high.hpp>

#endif
