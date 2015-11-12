//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_TYPES_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_TYPES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Types injection into boost.simd
// Injects or define some basic types in boost::simd for consistency sake.
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/dispatch/meta/make_integer.hpp>

namespace boost { namespace simd
{
  typedef boost::dispatch::meta::make_integer<1,unsigned>::type uint8_t;
  typedef boost::dispatch::meta::make_integer<2,unsigned>::type uint16_t;
  typedef boost::dispatch::meta::make_integer<4,unsigned>::type uint32_t;
  typedef boost::dispatch::meta::make_integer<8,unsigned>::type uint64_t;
  typedef boost::dispatch::meta::make_integer<1,signed>::type   int8_t;
  typedef boost::dispatch::meta::make_integer<2,signed>::type   int16_t;
  typedef boost::dispatch::meta::make_integer<4,signed>::type   int32_t;
  typedef boost::dispatch::meta::make_integer<8,signed>::type   int64_t;
} }

#endif
