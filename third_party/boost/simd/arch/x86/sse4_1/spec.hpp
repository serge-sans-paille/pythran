//==================================================================================================
/*!
  @file

  Defines the SSE4.1 specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if !defined(BOOST_SIMD_DEFAULT_FAMILY)
  #if BOOST_HW_SIMD_X86 == BOOST_HW_SIMD_X86_SSE4_1_VERSION
    #define BOOST_SIMD_DEFAULT_FAMILY ::boost::simd::sse_
    #define BOOST_SIMD_DEFAULT_SITE   ::boost::simd::sse4_1_
  #endif
#endif

#if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE4_1_VERSION
  #include <smmintrin.h>
  #include <boost/simd/arch/x86/sse4_1/as_simd.hpp>
  #include <boost/simd/arch/x86/sse4_1/pack_traits.hpp>
#endif

#endif
