//==================================================================================================
/*!
  @file

  Defines the SSE3 specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE3_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE3_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if !defined(BOOST_SIMD_DEFAULT_FAMILY)
  #if BOOST_HW_SIMD_X86 == BOOST_HW_SIMD_X86_SSE3_VERSION
    #define BOOST_SIMD_DEFAULT_FAMILY ::boost::simd::sse_
    #define BOOST_SIMD_DEFAULT_SITE   ::boost::simd::sse3_
  #endif
#endif

#if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE3_VERSION
  #include <pmmintrin.h>
  #include <boost/simd/arch/x86/sse3/as_simd.hpp>
  #include <boost/simd/arch/x86/sse3/pack_traits.hpp>
#endif

#endif
