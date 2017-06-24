//==================================================================================================
/*!
  @file

  Convenience header for SIMD detection

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PREDEF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PREDEF_HPP_INCLUDED

#include <boost/version.hpp>

/*
  Force the setup of specific SIMD x86 extension on MSVC.

  As MSVC doesn't have /ARCH: option for each special extension in the SSE family, we emulate
  it via the use of the BOOST_SIMD_HAS_xxx_SUPPORT macro before using Boost.Predef detection
  system.
*/

#if defined(_MSC_VER)
  #if defined(BOOST_SIMD_ASSUME_SSE3)
    #define __SSE3__
  #endif

  #if defined(BOOST_SIMD_ASSUME_SSSE3)
    #define __SSSE3__
  #endif

  #if defined(BOOST_SIMD_ASSUME_SSE4_1)
    #define __SSE4_1__
  #endif

  #if defined(BOOST_SIMD_ASSUME_SSE4_2)
    #define __SSE4_2__
  #endif

  #if defined(BOOST_SIMD_ASSUME_SSE4A)
    #define __SSE4A__
  #endif

  #if defined(BOOST_SIMD_ASSUME_XOP)
    #define __XOP__
  #endif

  #if defined(BOOST_SIMD_ASSUME_FMA4)
    #define __FMA4__
  #endif

  #if defined(BOOST_SIMD_ASSUME_FMA3)
    #define __FMA3__
  #endif

  #if defined(BOOST_SIMD_ASSUME_MIC)
    #define __MIC__
  #endif
#endif

// We assume that everything is gonna be fixed in boost 1.62
#if BOOST_VERSION <= 107200
  #include <boost/simd/detail/predef/hardware/simd.h>
#else
  #include <boost/predef/hardware/simd.h>
#endif

// This one is missing from current predef
#if defined(__BYTE_ORDER__)
  #if !defined(__BYTE_ORDER)
    #define __BYTE_ORDER __BYTE_ORDER__
  #endif
#endif
#include <boost/predef/other/endian.h>

// Ensure a cross X86/AMD selection
#if BOOST_HW_SIMD_X86 > BOOST_HW_SIMD_X86_AMD
  #define BOOST_HW_SIMD_X86_OR_AMD BOOST_HW_SIMD_X86
#else
  #define BOOST_HW_SIMD_X86_OR_AMD BOOST_HW_SIMD_X86_AMD
#endif

#if defined(BOOST_HW_SIMD_X86_AVAILABLE) || defined(BOOST_HW_SIMD_X86_AMD_AVAILABLE)
  #define BOOST_HW_SIMD_X86_OR_AMD_AVAILABLE
#endif

#endif
