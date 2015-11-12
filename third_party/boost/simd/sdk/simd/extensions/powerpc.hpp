//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions/powerpc/qpx.hpp>
#include <boost/simd/sdk/simd/extensions/powerpc/vsx.hpp>
#include <boost/simd/sdk/simd/extensions/powerpc/vmx.hpp>

#if defined(BOOST_SIMD_HAS_VSX_SUPPORT)
  #if !defined(BOOST_SIMD_VR_COUNT)
  #define BOOST_SIMD_VR_COUNT 64u
  #endif
#elif defined(BOOST_SIMD_HAS_VMX_SUPPORT) || defined(BOOST_SIMD_HAS_QPX_SUPPORT)
  #if !defined(BOOST_SIMD_VR_COUNT)
  #define BOOST_SIMD_VR_COUNT 32u
  #endif
#endif

#if defined(BOOST_SIMD_HAS_VMX_SUPPORT) || defined(BOOST_SIMD_HAS_QPX_SUPPORT)
  #if !defined(BOOST_SIMD_GPR_COUNT)
  #define BOOST_SIMD_GPR_COUNT  32u
  #endif
#endif

#endif
