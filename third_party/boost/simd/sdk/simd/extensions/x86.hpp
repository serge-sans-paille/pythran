//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check for the most recent SSE family extension
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/extensions/x86/mic.hpp>
#include <boost/simd/sdk/simd/extensions/x86/avx2.hpp>
#include <boost/simd/sdk/simd/extensions/x86/fma3.hpp>
#include <boost/simd/sdk/simd/extensions/x86/xop.hpp>
#include <boost/simd/sdk/simd/extensions/x86/fma4.hpp>
#include <boost/simd/sdk/simd/extensions/x86/avx.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4_2.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4_1.hpp>
#include <boost/simd/sdk/simd/extensions/x86/ssse3.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4a.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse3.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse2.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse.hpp>

#if   defined(BOOST_SIMD_HAS_SSE_SUPPORT)
  #if defined(BOOST_SIMD_ARCH_X86_64)

    #if !defined(BOOST_SIMD_GPR_COUNT)
    #define BOOST_SIMD_GPR_COUNT 16u
    #endif

    #if !defined(BOOST_SIMD_VR_COUNT)
    #define BOOST_SIMD_VR_COUNT  16u
    #endif

  #elif defined(BOOST_SIMD_ARCH_X86)
    #if !defined(BOOST_SIMD_GPR_COUNT)
    #define BOOST_SIMD_GPR_COUNT 8u
    #endif

    #if !defined(BOOST_SIMD_VR_COUNT)
    #define BOOST_SIMD_VR_COUNT  8u
    #endif
  #endif
#endif

#endif
