//==================================================================================================
/*!
  @file

  Defines the common CPU specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if !defined(BOOST_SIMD_DEFAULT_FAMILY)
  #define BOOST_SIMD_DEFAULT_FAMILY ::boost::simd::simd_emulation_
  #define BOOST_SIMD_DEFAULT_SITE   ::boost::dispatch::cpu_
  #define BOOST_SIMD_STRICT_EMULATION
#endif

// Used as fallbacks for generic cases
#include <boost/simd/arch/common/simd/abi_of.hpp>
#include <boost/simd/arch/common/simd/as_simd.hpp>
#include <boost/simd/arch/common/simd/pack_traits.hpp>

#endif
