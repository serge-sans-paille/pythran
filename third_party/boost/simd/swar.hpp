//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_SWAR_HPP_INCLUDED
#define BOOST_SIMD_SWAR_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @defgroup group-swar Intra register Functions
    @ingroup  group-functions

    These functions provide algorithms for interleaving, aggregation, splitting and, more
    generally, wide register sub-element manipulation. These functions are usually only
    defined for SIMD types but may, in some cases, have a valid scalar semantic.
  **/
} }

#include <boost/simd/function/broadcast.hpp>
#include <boost/simd/function/deinterleave_first.hpp>
#include <boost/simd/function/deinterleave_second.hpp>
#include <boost/simd/function/enumerate.hpp>
#include <boost/simd/function/fmasubadd.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/lookup.hpp>
#include <boost/simd/function/reverse.hpp>
#include <boost/simd/function/sort.hpp>
#include <boost/simd/function/maximum.hpp>
#include <boost/simd/function/minimum.hpp>
#include <boost/simd/function/prod.hpp>
#include <boost/simd/function/sum.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/subadd.hpp>

#endif
